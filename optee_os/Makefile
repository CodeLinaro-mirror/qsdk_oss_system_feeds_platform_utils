include $(TOPDIR)/rules.mk

PKG_NAME:=optee-os
PKG_RELEASE:=1
PKG_VERSION:=4.6.0

PKG_SOURCE:=optee_os-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL_FILE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/OP-TEE/optee_os/archive/refs/tags
PKG_HASH:=0c947c6972bf50c483cb993af01041d4094b1e03711c7246cdde6ba2ffc351fe

PKG_BUILD_DIR:=$(BUILD_DIR)/optee_os-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=@TARGET_ipq96xx||TARGET_ipq52xx
	TITLE:=OP-TEE OS TA dev kit (headers-only, virtual platform)
	URL:=https://github.com/OP-TEE/optee_os
endef

define Package/$(PKG_NAME)/Description
	Builds optee_os for a lightweight virtual platform (vexpress-qemu_armv8a)
	solely to produce the TA dev kit (headers, tee_api/PTA UUIDs,
	host_include, conf.mk) that optee_test's xtest needs to compile. This
	does NOT produce anything that runs on IPQ hardware - no IPQ platform
	support exists upstream in optee_os.
endef

# vexpress-qemu_armv8a forces CFG_ARM64_core=y and supports ta_arm64, so it
# produces a real arm64 TA dev kit export with no IPQ hardware dependency.
OPTEE_OS_PLATFORM:=vexpress-qemu_armv8a
OPTEE_OS_OUT:=$(PKG_BUILD_DIR)/out/arm-plat-vexpress

define Build/Compile
	+$(MAKE) -C $(PKG_BUILD_DIR) \
		PLATFORM=$(OPTEE_OS_PLATFORM) \
		CROSS_COMPILE64="$(TARGET_CROSS)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		CFG_USER_TA_TARGETS=ta_arm64 \
		CFG_BUILD_IN_TREE_TA=n \
		ta_dev_kit
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib/optee_os/export-ta_arm64
	$(CP) $(OPTEE_OS_OUT)/export-ta_arm64/* $(1)/usr/lib/optee_os/export-ta_arm64/
endef

# Headers-only package: nothing runs on the target, so there is no
# Package/$(PKG_NAME)/install - it only participates in the build (staging)
# phase for other packages such as optee_test.

$(eval $(call BuildPackage,$(PKG_NAME)))
