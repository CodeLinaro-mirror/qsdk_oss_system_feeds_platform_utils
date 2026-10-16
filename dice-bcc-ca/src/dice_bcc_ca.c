/*
 * Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 *
 * Userspace OP-TEE Client Application for DICE BCC functionality
 *
 * This application provides a userspace interface to retrieve DICE
 * (Device Identifier Composition Engine) BCC (Boot Certificate Chain)
 * certificates from TME via the DICE BCC PTA running in OP-TEE secure world.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <tee_client_api.h>

/*
 * DICE BCC PTA Interface Definitions
 */

/* DICE BCC PTA UUID: 916857bf-9754-4aea-908f-930aa736c42e */
#define DICE_BCC_PTA_UUID \
    { 0x916857bf, 0x9754, 0x4aea, \
      { 0x90, 0x8f, 0x93, 0x0a, 0xa7, 0x36, 0xc4, 0x2e } }

/* Command IDs for PTA operations */
#define PTA_CMD_DICE_BCC_GET_CERT         0x00

/* DICE BCC buffer size (4096 bytes is sufficient) */
#define DICE_BCC_BUFFER_SIZE              4096

/* TME BCC status codes */
#define TMEBCC_STATUS_SUCCESS             0x0
#define TME_STATUS_INVALID_INPUT          0x2


/*
 * Global OP-TEE context and session
 */
static TEEC_Context ctx;
static TEEC_Session sess;
static int session_opened = 0;

/*
 * Initialize OP-TEE context and open session with DICE BCC PTA
 */
static int dice_bcc_init(void)
{
    TEEC_Result res;
    TEEC_UUID uuid = DICE_BCC_PTA_UUID;
    uint32_t err_origin;

    /* Initialize TEE context */
    res = TEEC_InitializeContext(NULL, &ctx);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InitializeContext failed with code 0x%x\n", res);
        return -1;
    }

    /* Open session with PTA */
    res = TEEC_OpenSession(&ctx, &sess, &uuid,
                          TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_OpenSession failed with code 0x%x origin 0x%x\n",
                res, err_origin);
        TEEC_FinalizeContext(&ctx);
        return -1;
    }

    session_opened = 1;
    return 0;
}

/*
 * Cleanup OP-TEE context and session
 */
static void dice_bcc_cleanup(void)
{
    if (session_opened) {
        TEEC_CloseSession(&sess);
        session_opened = 0;
    }
    TEEC_FinalizeContext(&ctx);
}

/*
 * Retrieve DICE BCC certificate from TME via OP-TEE PTA
 * Returns: certificate size on success, -1 on error
 */
static ssize_t dice_bcc_get_cert(void *cert_buf, size_t buf_size)
{
    TEEC_Result res;
    TEEC_Operation op;
    TEEC_SharedMemory shm;
    uint32_t err_origin;
    ssize_t cert_size = -1;
    uint32_t tme_status;

    if (!cert_buf || buf_size < DICE_BCC_BUFFER_SIZE) {
        fprintf(stderr, "Invalid buffer parameters\n");
        return -1;
    }

    /* Allocate shared memory for certificate output */
    shm.size = DICE_BCC_BUFFER_SIZE;
    shm.flags = TEEC_MEM_OUTPUT;

    res = TEEC_AllocateSharedMemory(&ctx, &shm);
    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_AllocateSharedMemory failed with code 0x%x\n", res);
        return -1;
    }

    /* Prepare operation parameters */
    memset(&op, 0, sizeof(op));
    op.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_WHOLE,
                                     TEEC_NONE,
                                     TEEC_NONE,
                                     TEEC_NONE);

    /* param[0]: Output buffer for certificate */
    op.params[0].memref.parent = &shm;
    op.params[0].memref.offset = 0;
    op.params[0].memref.size = DICE_BCC_BUFFER_SIZE;

    /* Invoke PTA command to get certificate */
    res = TEEC_InvokeCommand(&sess, PTA_CMD_DICE_BCC_GET_CERT, &op, &err_origin);

    if (res != TEEC_SUCCESS) {
        fprintf(stderr, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x\n",
                res, err_origin);
        goto cleanup;
    }

    /* Check TME status (returned in TEEC_Result) */
    tme_status = res;

    if (tme_status == TMEBCC_STATUS_SUCCESS) {
        /* Get actual certificate size from operation */
        cert_size = op.params[0].memref.size;

        if (cert_size > DICE_BCC_BUFFER_SIZE) {
            fprintf(stderr, "Invalid certificate size: %zu\n", cert_size);
            cert_size = -1;
            goto cleanup;
        }

        /* Copy certificate to output buffer */
        memcpy(cert_buf, shm.buffer, cert_size);

    } else if (tme_status == TME_STATUS_INVALID_INPUT) {
        fprintf(stderr, "TME reported invalid input parameters\n");
    } else {
        fprintf(stderr, "TME-side failure, status=0x%x\n", tme_status);
    }

cleanup:
    TEEC_ReleaseSharedMemory(&shm);
    return cert_size;
}

/*
 * Write certificate to file
 */
static int write_cert_to_file(const char *path, const void *cert_buf, size_t cert_size)
{
    int fd;
    ssize_t written;

    fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file %s: %s\n", path, strerror(errno));
        return -1;
    }

    written = write(fd, cert_buf, cert_size);
    if (written != (ssize_t)cert_size) {
        fprintf(stderr, "Failed to write certificate: expected %zu, wrote %zd\n",
                cert_size, written);
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}


/*
 * Get certificate and write to output
 */
static int cmd_get_cert(const char *output_path, int verbose)
{
    void *cert_buf;
    ssize_t cert_size;
    int ret = -1;

    if (verbose) {
        fprintf(stderr, "Retrieving DICE BCC certificate from TME...\n");
    }

    /* Allocate buffer for certificate */
    cert_buf = malloc(DICE_BCC_BUFFER_SIZE);
    if (!cert_buf) {
        fprintf(stderr, "Failed to allocate certificate buffer\n");
        return -1;
    }

    /* Initialize OP-TEE session */
    if (dice_bcc_init() != 0) {
        fprintf(stderr, "Failed to initialize DICE BCC client\n");
        free(cert_buf);
        return -1;
    }

    /* Get certificate from TME */
    cert_size = dice_bcc_get_cert(cert_buf, DICE_BCC_BUFFER_SIZE);
    if (cert_size < 0) {
        fprintf(stderr, "Failed to retrieve certificate from TME\n");
        dice_bcc_cleanup();
        free(cert_buf);
        return -1;
    }

    if (verbose) {
        fprintf(stderr, "Successfully retrieved certificate (%zu bytes)\n", cert_size);
    }

    dice_bcc_cleanup();

    /* Write to output file or stdout */
    if (output_path) {
        ret = write_cert_to_file(output_path, cert_buf, cert_size);
        if (ret == 0 && verbose) {
            fprintf(stderr, "Certificate written to %s\n", output_path);
        }
    } else {
        /* Write to stdout */
        if (fwrite(cert_buf, 1, cert_size, stdout) != (size_t)cert_size) {
            fprintf(stderr, "Failed to write certificate to stdout\n");
            ret = -1;
        } else {
            ret = 0;
        }
    }

    free(cert_buf);
    return ret;
}

/*
 * Print usage information
 */
static void print_usage(const char *prog_name)
{
    printf("Usage: %s [OPTIONS]\n", prog_name);
    printf("\n");
    printf("DICE BCC Certificate Client Application\n");
    printf("Retrieve DICE Boot Certificate Chain from TME via OP-TEE\n");
    printf("\n");
    printf("Options:\n");
    printf("  -o, --output FILE          Write certificate to FILE (default: stdout)\n");
    printf("  -v, --verbose              Enable verbose output\n");
    printf("  -h, --help                 Display this help message\n");
    printf("\n");
    printf("Examples:\n");
    printf("  # Get certificate and write to file\n");
    printf("  %s --output cert.bin\n", prog_name);
    printf("\n");
    printf("  # Get certificate to stdout (can pipe to other tools)\n");
    printf("  %s > cert.bin\n", prog_name);
    printf("\n");
    printf("  # With verbose output\n");
    printf("  %s --output cert.bin --verbose\n", prog_name);
}

/*
 * Main entry point
 */
int main(int argc, char *argv[])
{
    int opt;
    int verbose = 0;
    char *output_path = NULL;
    int ret = 0;

    static struct option long_options[] = {
        {"output",     required_argument, 0, 'o'},
        {"verbose",    no_argument,       0, 'v'},
        {"help",       no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    /* Parse command line options */
    while ((opt = getopt_long(argc, argv, "o:vh", long_options, NULL)) != -1) {
        switch (opt) {
        case 'o':
            output_path = optarg;
            break;
        case 'v':
            verbose = 1;
            break;
        case 'h':
            print_usage(argv[0]);
            return 0;
        default:
            print_usage(argv[0]);
            return 1;
        }
    }

    if (verbose) {
        printf("DICE BCC Client Application v1.0\n");
        printf("=================================\n\n");
    }

    /* Get certificate from TME and write to output */
    ret = cmd_get_cert(output_path, verbose);
    if (ret != 0) {
        fprintf(stderr, "Failed to get certificate\n");
        return 1;
    }

    if (verbose && output_path) {
        printf("Certificate retrieved successfully\n");
    }

    return 0;
}
