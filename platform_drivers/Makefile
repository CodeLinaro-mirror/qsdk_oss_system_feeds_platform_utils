include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=platform_drivers
PKG_VERSION:=1

define Build/Prepare
endef

define Build/Configure
endef

define Build/Compile
endef

OTHER_MENU:=Other modules

define KernelPackage/bootconfig
  SUBMENU:=$(OTHER_MENU)
  TITLE:=Bootconfig partition for failsafe
  KCONFIG:=CONFIG_BOOTCONFIG_PARTITION
  FILES:=$(LINUX_DIR)/drivers/platform/msm/bootconfig.ko@lt4.4 \
	$(LINUX_DIR)/drivers/platform/ipq/bootconfig.ko@ge4.4
  AUTOLOAD:=$(call AutoLoad,56,bootconfig,1)
endef

define KernelPackage/bootconfig/description
  Bootconfig partition for failsafe
endef

$(eval $(call KernelPackage,bootconfig))

define KernelPackage/qseecom
  SUBMENU:=$(OTHER_MENU)
  TITLE:=QSEECOM Client Test Driver
  KCONFIG:=CONFIG_QSEECOM
  FILES:=$(LINUX_DIR)/drivers/misc/qseecom.ko
  AUTOLOAD:=$(call AutoLoad,09,qseecom)
endef

define KernelPackage/qseecom/description
 QSEECOM Client Test Driver based on SCM interface
endef

$(eval $(call KernelPackage,qseecom))

define KernelPackage/fw-auth-test
  CATEGORY:=Kernel modules
  SUBMENU:=$(OTHER_MENU)
  TITLE:=Test module for Wifi FW Authentication
  KCONFIG:=CONFIG_FW_AUTH_TEST
  FILES:=$(LINUX_DIR)/drivers/misc/fw_auth_test.ko
endef

define KernelPackage/fw-auth-test/description
  This test module provides sysfs interface to provide data to test
the FW authentication API and display the results.
endef

$(eval $(call KernelPackage,fw-auth-test))

define KernelPackage/test-udelay
  CATEGORY:=Kernel modules
  SUBMENU:=$(OTHER_MENU)
  TITLE:=Test module for Udelay
  KCONFIG:=CONFIG_TEST_UDELAY
  FILES:=$(LINUX_DIR)/kernel/time/test_udelay.ko
endef

define KernelPackage/test-udelay/description
  This test module provides sysfs interface to test that udelay() is working
properly.
endef

$(eval $(call KernelPackage,test-udelay))

SOUND_MENU:=Sound Support

define AddPlatformDepends/sound
  SUBMENU:=$(SOUND_MENU)
  DEPENDS+=kmod-sound-core $(1)
endef

define KernelPackage/sound-soc-ipq
  TITLE:=Qualcomm-Atheros IPQ board soundcard support
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq807x||TARGET_ipq @!TARGET_ipq_ipq60xx @!TARGET_ipq_ipq60xx_64 +kmod-sound-soc-core
  KCONFIG:= \
	CONFIG_SND_QCA_SOC \
	CONFIG_SND_QCA_SOC_IPQ40XX \
	CONFIG_SND_SOC_QCOM=y \
	CONFIG_SND_SOC_IPQ=y \
	CONFIG_SND_SOC_IPQ_CODEC=y
  FILES:= \
	$(LINUX_DIR)/sound/soc/qca/snd-soc-ipq40xx-codec.ko@lt4.4 \
	$(LINUX_DIR)/sound/soc/qcom/ipq/snd-soc-ipq-codec.ko@ge4.4
  $(call AddPlatformDepends/sound)
endef

define KernelPackage/sound-soc-ipq/description
 This enables sound card support for Qualcomm-Atheros IPQ board
endef

$(eval $(call KernelPackage,sound-soc-ipq))

VIDEO_MENU:=Video Support

define KernelPackage/qpic_panel_ili_qvga
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=ILI QVGA Panel support
  KCONFIG:=CONFIG_FB_MSM_QPIC_ILI_QVGA_PANEL
  FILES:=$(LINUX_DIR)/drivers/video/msm/mdss/qpic_panel_ili_qvga.ko
endef

define KernelPackage/qpic_panel_ili_qvga/description
 Kernel support for qpic_panel_ili_qvga  lcd panel
endef

$(eval $(call KernelPackage,qpic_panel_ili_qvga))

define KernelPackage/qpic_panel_ertft
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=ERT TFT  Panel support
  KCONFIG:=CONFIG_FB_MSM_QPIC_ER_SSD1963_PANEL
  FILES:=$(LINUX_DIR)/drivers/video/msm/mdss/qpic_panel_er_ssd1963.ko
endef

define KernelPackage/qpic_panel_ertft/description
 Kernel support for qpic_panel_ertft  lcd panel
endef

$(eval $(call KernelPackage,qpic_panel_ertft))

CRYPTO_MENU:=Cryptographic API modules

define AddPlatformDepends/crypto
  SUBMENU:=$(CRYPTO_MENU)
  DEPENDS+=+kmod-crypto-core $(1)
endef

define KernelPackage/crypto-qcrypto
  TITLE:=QTI crypto CE engine
  KCONFIG:= \
	CONFIG_CRYPTO_DEV_QCRYPTO \
	CONFIG_CRYPTO_DEV_QCEDEV
  FILES:= \
	$(LINUX_DIR)/drivers/crypto/msm/qcrypto.ko \
	$(LINUX_DIR)/drivers/crypto/msm/qcedev.ko
  AUTOLOAD:=$(call AutoLoad,09,qcrypto)
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq40xx||TARGET_ipq_ipq40xx +kmod-crypto-manager +kmod-crypto-aes +kmod-crypto-hash +kmod-crypto-des
  $(call AddPlatformDepends/crypto)
endef

$(eval $(call KernelPackage,crypto-qcrypto))

define KernelPackage/crypto-qce
  TITLE:=QTI Crypto Engine (QCE)
  KCONFIG:= \
	CONFIG_CRYPTO_DEV_QCE
  FILES:= \
	$(LINUX_DIR)/drivers/crypto/qce/qcrypto.ko
  AUTOLOAD:=$(call AutoLoad,09,qcrypto)
  DEPENDS:=@TARGET_ipq807x||TARGET_ipq_ipq807x||TARGET_ipq_ipq807x_64||TARGET_ipq60xx||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64 +kmod-crypto-manager +kmod-crypto-aes +kmod-crypto-hash +kmod-crypto-des
  $(call AddPlatformDepends/crypto)
endef

$(eval $(call KernelPackage,crypto-qce))

USB_MENU:=USB Support

define AddPlatformDepends/usb
  SUBMENU:=$(USB_MENU)
  DEPENDS+=+kmod-usb-core $(1)
endef

define KernelPackage/usb-ath79
  TITLE:=ATH79 USB driver
  DEPENDS:=@TARGET_ar71xx +kmod-usb2
  KCONFIG:=CONFIG_USB_EHCI_HCD_ATH79
  FILES:=$(LINUX_DIR)/drivers/usb/host/ehci-ath79.ko
  AUTOLOAD:=$(call AutoLoad,40,ehci-ath79,1)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-ath79/description
 This driver provides USB Device Controller support for the
 ATH79 EHCI USB
endef

$(eval $(call KernelPackage,usb-ath79))

define KernelPackage/usb-configfs
 TITLE:= USB functions
  KCONFIG:=CONFIG_USB_CONFIGFS \
	CONFIG_USB_CONFIGFS_SERIAL=n \
	CONFIG_USB_CONFIGFS_ACM=n \
	CONFIG_USB_CONFIGFS_OBEX=n \
	CONFIG_USB_CONFIGFS_NCM=n \
	CONFIG_USB_CONFIGFS_ECM=n \
	CONFIG_USB_CONFIGFS_ECM_SUBSET=n \
	CONFIG_USB_CONFIGFS_RNDIS=n \
	CONFIG_USB_CONFIGFS_EEM=n \
	CONFIG_USB_CONFIGFS_MASS_STORAGE=n \
	CONFIG_USB_CONFIGFS_F_LB_SS=n \
	CONFIG_USB_CONFIGFS_F_FS=n \
	CONFIG_USB_CONFIGFS_F_UAC1=n \
	CONFIG_USB_CONFIGFS_F_UAC2=n \
	CONFIG_USB_CONFIGFS_F_MIDI=n \
	CONFIG_USB_CONFIGFS_F_HID=n \
	CONFIG_USB_CONFIGFS_F_PRINTER=n \
	CONFIG_USB_CONFIGFS_F_QDSS=n
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-configfs/description
 USB functions
endef

$(eval $(call KernelPackage,usb-configfs))

define KernelPackage/usb-f-diag
  TITLE:=USB DIAG
  KCONFIG:=CONFIG_USB_F_DIAG \
	CONFIG_USB_CONFIGFS_F_DIAG=y \
	CONFIG_DIAG_OVER_USB=y
  DEPENDS:=+kmod-usb-lib-composite +kmod-usb-configfs
  FILES:=$(LINUX_DIR)/drivers/usb/gadget/function/usb_f_diag.ko
  AUTOLOAD:=$(call AutoLoad,52,usb_f_diag)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-f-diag/description
 USB DIAG
endef

$(eval $(call KernelPackage,usb-f-diag))

define KernelPackage/usb-uas
  TITLE:=USB Attched SCSI support
  DEPENDS:= +kmod-scsi-core +kmod-usb-storage
  KCONFIG:=CONFIG_USB_UAS
  FILES:=$(LINUX_DIR)/drivers/usb/storage/uas.ko
  AUTOLOAD:=$(call AutoProbe,uas,1)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-uas/description
 Kernel support for USB Attached SCSI devices (UAS)
endef

$(eval $(call KernelPackage,usb-uas))

define KernelPackage/usb-chipidea-qti
  TITLE:=ChipIdea controllers support
  DEPENDS:= +kmod-usb2 +USB_GADGET_SUPPORT:kmod-usb-gadget @TARGET_ipq_ipq806x
  KCONFIG:=\
	CONFIG_USB_CHIPIDEA \
	CONFIG_USB_CHIPIDEA_HOST=y \
	CONFIG_USB_CHIPIDEA_UDC=y \
	CONFIG_USB_CHIPIDEA_DEBUG=y
	FILES:=\
	  $(LINUX_DIR)/drivers/extcon/extcon.ko@ge4.3 \
	  $(LINUX_DIR)/drivers/usb/chipidea/ci_hdrc.ko \
	  $(LINUX_DIR)/drivers/usb/chipidea/ci_hdrc_msm.ko
  AUTOLOAD :=$(call AutoLoad,51,extcon ci_hdrc ci_hdrc_msm)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-chipidea-msm/description
  Kernel support for USB ChipIdea controllers
endef

$(eval $(call KernelPackage,usb-chipidea-qti))


define KernelPackage/usb-phy-ci-qti
  TITLE:=Chipidea USB PHY driver
  DEPENDS:=+kmod-usb-chipidea-qti @TARGET_ipq_ipq806x
  KCONFIG:=CONFIG_USB_MSM_OTG
  FILES:=$(LINUX_DIR)/drivers/usb/phy/phy-msm-usb.ko
  AUTOLOAD:=$(call AutoLoad,50,phy-msm-usb)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-phy-ci-qti/description
  Kernel support for qti chipidea USB PHY
endef

$(eval $(call KernelPackage,usb-phy-ci-qti))
define KernelPackage/usb-gzero
  TITLE:=USB GZERO support
  KCONFIG:=CONFIG_USB_ZERO
  FILES:=\
       $(LINUX_DIR)/drivers/usb/gadget/g_zero.ko
  AUTOLOAD:=$(call AutoLoad,45,g_zero)
  DEPENDS:=+kmod-usb-lib-composite +kmod-usb-configfs +kmod-lib-crc-ccitt
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-gzero/description
 Kernel support for USB gzero mode
endef

$(eval $(call KernelPackage,usb-gzero))

define KernelPackage/usb-gdiag
  TITLE:=USB GDIAG support
  KCONFIG:=CONFIG_USB_G_DIAG
  FILES:=\
       $(LINUX_DIR)/drivers/usb/gadget/legacy/g_diag.ko
  AUTOLOAD:=$(call AutoLoad,52,g_diag)
  DEPENDS:=@TARGET_ipq60xx||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64 +kmod-usb-gadget +kmod-usb-lib-composite
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-gdiag/description
 Kernel support for USB gdiag mode
endef

$(eval $(call KernelPackage,usb-gdiag))

define KernelPackage/usb-f_ss_lb
  TITLE:=USB F_SS_LB support
  KCONFIG:=CONFIG_USB_F_SS_LB
  FILES:=\
        $(LINUX_DIR)/drivers/usb/gadget/usb_f_ss_lb.ko
  AUTOLOAD:=$(call AutoLoad,45,usb_f_ss_lb)
  DEPENDS:=+kmod-usb-lib-composite +kmod-usb-configfs +kmod-lib-crc-ccitt
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-f_ss_lb/description
 Kernel support for USB f_ss_lb mode
endef

$(eval $(call KernelPackage,usb-f_ss_lb))


define KernelPackage/diag-char
  TITLE:=CHAR DIAG
  KCONFIG:=CONFIG_DIAGFWD_BRIDGE_CODE=y \
	  CONFIG_DIAG_CHAR
  DEPENDS:=+kmod-lib-crc-ccitt +USB_CONFIGFS_F_DIAG:kmod-usb-f-diag +USB_CONFIGFS_F_DIAG:kmod-usb-core
  FILES:=$(LINUX_DIR)/drivers/char/diag/diagchar.ko
  AUTOLOAD:=$(call AutoLoad,52,diagchar)
endef

define KernelPackage/diag-char/description
 CHAR DIAG
endef

$(eval $(call KernelPackage,diag-char))

define KernelPackage/usb-f-qdss
  TITLE:=USB QDSS
  KCONFIG:=CONFIG_USB_F_QDSS \
	CONFIG_USB_CONFIGFS_F_QDSS=y
  DEPENDS:=@TARGET_ipq807x||TARGET_ipq60xx||TARGET_ipq_ipq807x||TARGET_ipq_ipq807x_64||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64 +kmod-usb-lib-composite +kmod-usb-configfs +kmod-lib-crc-ccitt +kmod-usb-dwc3 +TARGET_ipq_ipq60xx:kmod-usb-dwc3-qcom +TARGET_ipq_ipq60xx_64:kmod-usb-dwc3-qcom +TARGET_ipq_ipq807x:kmod-usb-dwc3-of-simple +TARGET_ipq_ipq807x_64:kmod-usb-dwc3-of-simple +TARGET_ipq60xx:kmod-usb-dwc3-qcom +TARGET_ipq60xx:kmod-usb-dwc3-of-simple +TARGET_ipq807x:kmod-usb-dwc3-qcom +TARGET_ipq807x:kmod-usb-dwc3-of-simple
  FILES:=$(LINUX_DIR)/drivers/usb/gadget/function/usb_f_qdss.ko \
	$(LINUX_DIR)/drivers/usb/gadget/function/u_qdss.ko
  AUTOLOAD:=$(call AutoLoad,52,usb_f_qdss)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-f-qdss/description
 USB QDSS
endef

$(eval $(call KernelPackage,usb-f-qdss))

LEDS_MENU:=LED modules

define KernelPackage/leds-tlc591xx
  SUBMENU:=$(LEDS_MENU)
  TITLE:=TLC591XX LED support
  DEPENDS:=+kmod-i2c-core +kmod-regmap
  KCONFIG:=CONFIG_LEDS_TLC591XX
  FILES:=$(LINUX_DIR)/drivers/leds/leds-tlc591xx.ko
  AUTOLOAD:=$(call AutoLoad,60,leds-tlc591xx,1)
endef

define KernelPackage/leds-tlc591xx/description
  Driver for the TLC591XX I2C LED controllers.
endef

$(eval $(call KernelPackage,leds-tlc591xx))
