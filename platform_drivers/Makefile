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
  DEPENDS+=@TARGET_ipq95xx||TARGET_ipq53xx
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

define KernelPackage/qpic_panel_ertft
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=ERT TFT  Panel support
  KCONFIG:=CONFIG_FB_MSM_QPIC_ER_SSD1963_PANEL@lt4.4 \
	CONFIG_FB_QCOM_QPIC_ER_SSD1963_PANEL@le4.4 \
	CONFIG_FB_QTI_QPIC_ER_SSD1963_PANEL@ge5.4
  FILES:=$(LINUX_DIR)/drivers/video/msm/mdss/qpic_panel_er_ssd1963.ko@lt4.4 \
	$(LINUX_DIR)/drivers/video/fbdev/qcom/qpic_panel_er_ssd1963.ko@le4.4 \
	$(LINUX_DIR)/drivers/video/fbdev/qti/qpic_panel_er_ssd1963.ko@ge5.4
endef

define KernelPackage/qpic_panel_ertft/description
 Kernel support for qpic_panel_ertft  lcd panel
endef

$(eval $(call KernelPackage,qpic_panel_ertft))

CRYPTO_MENU:=Cryptographic API modules

define AddPlatformDepends/crypto
  SUBMENU:=$(CRYPTO_MENU)
  DEPENDS+=+LINUX_4_4:kmod-crypto-core $(1)
endef

define KernelPackage/crypto-aes-internal
  TITLE:=AES cipher CryptoAPI module
  KCONFIG:=CONFIG_CRYPTO_AES CONFIG_CRYPTO_AES_586
  FILES:=$(LINUX_DIR)/crypto/aes_generic.ko
  AUTOLOAD:=$(call AutoLoad,09,aes_generic)
  $(call AddDepends/crypto)
endef

$(eval $(call KernelPackage,crypto-aes-internal))

define KernelPackage/crypto-qce
  TITLE:=QTI Crypto Engine (QCE)
  KCONFIG:= \
	CONFIG_CRYPTO_DEV_QCE \
	CONFIG_CRYPTO_DEV_QCE_ENABLE_ALL=y@ge5.4 \
	CONFIG_CRYPTO_DEV_QCE_SKCIPHER=y \
	CONFIG_CRYPTO_DEV_QCE_AEAD=y \
	CONFIG_CRYPTO_DEV_QCE_ENABLE_SKCIPHER=n@ge5.4 \
	CONFIG_CRYPTO_DEV_QCE_ENABLE_SHA=n@ge5.4 \
	CONFIG_CRYPTO_DEV_QCE_SW_MAX_LEN=0@ge5.4 \
	CONFIG_CRYPTO_DEV_QCE_ENABLE_AEAD=n \
	CONFIG_CRYPTO_DEV_QCE_SHA=y
  FILES:= \
	$(LINUX_DIR)/drivers/crypto/qce/qcrypto.ko
  AUTOLOAD:=$(call AutoLoad,09,qcrypto)
  DEPENDS:=@TARGET_ipq807x||TARGET_ipq_ipq807x||TARGET_ipq_ipq807x_64||TARGET_ipq60xx||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64||TARGET_ipq_ipq50xx||TARGET_ipq_ipq50xx_64||TARGET_ipq95xx||TARGET_ipq50xx||TARGET_ipq54xx +kmod-crypto-manager +LINUX_4_4:kmod-crypto-aes-internal +kmod-crypto-hash +LINUX_4_4:kmod-crypto-des +kmod-crypto-authenc
  $(call AddPlatformDepends/crypto)
endef

$(eval $(call KernelPackage,crypto-qce))

define KernelPackage/crypto-seccrypt
  TITLE:=QTI Crypto Secure Crypt (QSC)
  KCONFIG:= \
	CONFIG_SECCRYPT
  FILES:= \
	$(LINUX_DIR)/drivers/crypto/seccrypt.ko
  AUTOLOAD:=$(call AutoLoad,09,seccrypt)
  DEPENDS:=@TARGET_ipq53xx||TARGET_ipq54xx
  $(call AddPlatformDepends/crypto)
endef

$(eval $(call KernelPackage,crypto-seccrypt))

USB_MENU:=USB Support

define AddPlatformDepends/usb
  SUBMENU:=$(USB_MENU)
  DEPENDS+=+kmod-usb-core $(1)
endef

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

define KernelPackage/usb-uas
  TITLE:=USB Attched SCSI support
  DEPENDS:= +kmod-scsi-core +kmod-usb-storage
  KCONFIG:=CONFIG_USB_UAS
  FILES:=$(LINUX_DIR)/drivers/usb/storage/uas.ko
  AUTOLOAD:=$(call AutoProbe,uas)
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

define KernelPackage/usb-phy-ipq807x
  TITLE:=DWC3 USB QTI PHY drivers for IPQ807x based targets
  DEPENDS:=@TARGET_ipq||TARGET_ipq807x||TARGET_ipq95xx||TARGET_ipq60xx||TARGET_ipq54xx
  KCONFIG:= \
	CONFIG_PHY_QCOM_QUSB2 \
	CONFIG_PHY_QCOM_QMP=y \
	CONFIG_PHY_QCOM_QMP_USB=y \
	CONFIG_USB_QCOM_QUSB_PHY \
	CONFIG_USB_QCOM_QMP_PHY
  FILES:= \
	$(LINUX_DIR)/drivers/phy/qualcomm/phy-qcom-qusb2.ko@ge5.4 \
	$(LINUX_DIR)/drivers/usb/phy/phy-msm-qusb.ko@le4.4 \
	$(LINUX_DIR)/drivers/usb/phy/phy-msm-ssusb-qmp.ko@le4.4
  AUTOLOAD:=$(call AutoLoad,85,phy-qcom-qusb2 phy-msm-qusb phy-msm-ssusb-qmp)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-phy-ipq807x/description
  Support for USB PHY drivers in IPQ807x based SoCs.
endef

$(eval $(call KernelPackage,usb-phy-ipq807x))

define KernelPackage/usb-dwc3-internal
  TITLE:=DWC3 USB controller driver
  DEPENDS:=+USB_GADGET_SUPPORT:kmod-usb-gadget +USB_GADGET_SUPPORT:kmod-usb-roles
  KCONFIG:= \
	CONFIG_USB_DWC3 \
	CONFIG_USB_DWC3_HOST=n \
	CONFIG_USB_DWC3_GADGET=n \
	CONFIG_USB_DWC3_DUAL_ROLE=y \
	CONFIG_EXTCON=y \
	CONFIG_USB_DWC3_DEBUG=n \
	CONFIG_USB_DWC3_VERBOSE=n
  FILES:= $(LINUX_DIR)/drivers/usb/dwc3/dwc3.ko
  AUTOLOAD:=$(call AutoLoad,84,dwc3)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-dwc3-internal/description
 This driver provides support for the Dual Role SuperSpeed
 USB Controller based on the Synopsys DesignWare USB3 IP Core
endef

$(eval $(call KernelPackage,usb-dwc3-internal))

define KernelPackage/usb-dwc3-qcom-internal
  TITLE:=DWC3 QTI USB driver
  DEPENDS:=@!LINUX_4_14 @(TARGET_ipq40xx||TARGET_ipq806x||TARGET_ipq807x||TARGET_ipq60xx||TARGET_ipq95xx||TARGET_ipq50xx||TARGET_ipq53xx||TARGET_ipq54xx) +kmod-usb-dwc3-internal
  KCONFIG:= CONFIG_USB_DWC3_QCOM
  FILES:= $(LINUX_DIR)/drivers/usb/dwc3/dwc3-qcom.ko
  AUTOLOAD:=$(call AutoLoad,83,dwc3-qcom)
  $(call AddPlatformDepends/usb)
endef

define KernelPackage/usb-dwc3-qcom-internal/description
 Some QTI SoCs use DesignWare Core IP for USB2/3 functionality.
 This driver also handles Qscratch wrapper which is needed for
 peripheral mode support.
endef

$(eval $(call KernelPackage,usb-dwc3-qcom-internal))

define KernelPackage/usb-f-qdss
  TITLE:=USB QDSS
  KCONFIG:=CONFIG_USB_F_QDSS \
	CONFIG_USB_CONFIGFS_F_QDSS=y
  DEPENDS:=@TARGET_ipq54xx +kmod-usb-lib-composite +kmod-usb-configfs +kmod-lib-crc-ccitt +kmod-usb-dwc3-qcom-internal
  FILES:=$(LINUX_DIR)/drivers/usb/gadget/function/usb_f_qdss.ko
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
  AUTOLOAD:=$(call AutoLoad,60,leds-tlc591xx)
endef

define KernelPackage/leds-tlc591xx/description
  Driver for the TLC591XX I2C LED controllers.
endef

$(eval $(call KernelPackage,leds-tlc591xx))

define KernelPackage/mhitest_mod
  SUBMENU:=$(OTHER_MENU)
  TITLE:=MHI Test Module for qcn9000.
  DEPENDS+=@TARGET_ipq_ipq807x||TARGET_ipq_ipq807x_64||TARGET_ipq50xx||TARGET_ipq807x||TARGET_ipq60xx||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64||TARGET_ipq_ipq50xx||TARGET_ipq_ipq50xx_64||TARGET_ipq95xx||TARGET_ipq53xx||TARGET_ipq54xx
  KCONFIG:=CONFIG_MHI_BUS_TEST
  FILES:=$(LINUX_DIR)/drivers/bus/mhi/test/mhitest_mod.ko
endef

define KernelPackage/mhitest_mod/description
  Add MHI Test Module.
endef

$(eval $(call KernelPackage,mhitest_mod))

define KernelPackage/mhi_fuse_blower_mod
  SUBMENU:=$(OTHER_MENU)
  TITLE:=MHI Fuse Blower Module for qcn9224.
  DEPENDS+=@TARGET_ipq95xx||TARGET_ipq53xx||TARGET_ipq54xx
  KCONFIG:=
  FILES:=$(LINUX_DIR)/drivers/bus/mhi/fuse_blower/mhi_fuse_blower_mod.ko
endef

define KernelPackage/mhi_fuse_blower_mod/description
  Add MHI Fuse blower Module.
endef

$(eval $(call KernelPackage,mhi_fuse_blower_mod))

define KernelPackage/qmi_sample_client
  SUBMENU:=$(OTHER_MENU)
  TITLE:= Sample qmi test application.
  DEPENDS+=@TARGET_ipq807x||TARGET_ipq_ipq807x||TARGET_ipq_ipq807x_64||TARGET_ipq60xx||TARGET_ipq_ipq60xx||TARGET_ipq_ipq60xx_64||TARGET_ipq50xx||TARGET_ipq_ipq50xx||TARGET_ipq_ipq50xx_64||TARGET_ipq95xx||TARGET_ipq53xx||TARGET_ipq54xx

  KCONFIG:= \
	  CONFIG_SAMPLE_QMI_CLIENT
  FILES:= \
	  $(LINUX_DIR)/samples/qmi/qmi_sample_client.ko
  AUTOLOAD:=$(call AutoLoad,53,qmi_sample_client)
endef

define KernelPackage/qmi_sample_client/description
Add QMI ping_pong test application
endef

$(eval $(call KernelPackage,qmi_sample_client))

define KernelPackage/usb-phy-ipq5018
  TITLE:=DWC3 USB PHY driver for IPQ5018
  DEPENDS:=@TARGET_ipq50xx||TARGET_ipq53xx
  KCONFIG:= \
	CONFIG_USB_QCA_M31_PHY \
	CONFIG_PHY_QCOM_M31_USB \
	CONFIG_PHY_IPQ_UNIPHY_USB
  FILES:= \
	$(LINUX_DIR)/drivers/usb/phy/phy-qca-m31.ko@lt6.1 \
	$(LINUX_DIR)/drivers/phy/qualcomm/phy-qcom-m31.ko@ge6.1 \
	$(LINUX_DIR)/drivers/phy/phy-qca-uniphy.ko@le4.4 \
	$(LINUX_DIR)/drivers/phy/qualcomm/phy-qca-uniphy.ko@ge5.4
  AUTOLOAD:=$(call AutoLoad,85,phy-qca-m31 phy-qcom-m31 phy-qca-uniphy)
  $(call AddDepends/usb)
endef

define KernelPackage/usb-phy-ipq5018/description
 This driver provides support for the USB PHY drivers
 within the IPQ5018 SoCs.
endef

$(eval $(call KernelPackage,usb-phy-ipq5018))

define KernelPackage/llcc_perfmon
  SUBMENU:=$(OTHER_MENU)
  TITLE:=LLCC Perfmon Driver
  DEPENDS+=@TARGET_ipq54xx
  KCONFIG:=CONFIG_QCOM_LLCC_PERFMON
  FILES:=$(LINUX_DIR)/drivers/soc/qcom/llcc_perfmon.ko
endef

define KernelPackage/llcc_perfmon/description
  LLCC Perfmonance driver support
endef

$(eval $(call KernelPackage,llcc_perfmon))
