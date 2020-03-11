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
  DEPENDS+=kmod-sound-core $(1) @!TARGET_uml
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
