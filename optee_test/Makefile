include $(TOPDIR)/rules.mk

PKG_NAME:=optee-test
PKG_RELEASE:=1
PKG_VERSION:=4.6.0

PKG_SOURCE:=optee_test-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL_FILE:=$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/OP-TEE/optee_test/archive/refs/tags
PKG_HASH:=db4de73fa955a7db70a64a2c4ad1d2c48ddcb54c369821aba670fec6131a6f61

PKG_BUILD_DIR:=$(BUILD_DIR)/optee_test-$(PKG_VERSION)

PKG_BUILD_DEPENDS:=optee-os

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
	SECTION:=utils
	CATEGORY:=Utilities
	DEPENDS:=@TARGET_ipq96xx||TARGET_ipq52xx +libuuid +optee-client +optee-os +libopenssl
	TITLE:=Normal World Client side of the TEE
	URL:=https://github.com/OP-TEE/optee_test
endef

define Package/$(PKG_NAME)/Description
	This contains source code for the test suite (xtest) used to test the OP-TEE project.
endef

# No IPQ platform support exists in optee_os, so only the host-side xtest
# binary is built. TA_DEV_KIT_DIR points at the headers-only dev kit exported
# by the optee-os package (built for a virtual platform, see optee_os/Makefile).
MAKE_FLAGS += \
	OPTEE_CLIENT_EXPORT="$(STAGING_DIR)/usr" \
	TA_DEV_KIT_DIR="$(STAGING_DIR)/usr/lib/optee_os/export-ta_arm64"

define Build/Compile
	echo '#!/bin/sh' > $(PKG_BUILD_DIR)/cc-wrapper.sh
	echo 'exec $(TARGET_CC) -include sys/stat.h -ffile-prefix-map=$(PKG_BUILD_DIR)/= "$$$$@"' >> $(PKG_BUILD_DIR)/cc-wrapper.sh
	chmod +x $(PKG_BUILD_DIR)/cc-wrapper.sh
	+$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		$(MAKE_FLAGS) \
		CC="$(PKG_BUILD_DIR)/cc-wrapper.sh" \
		xtest
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/out/xtest/xtest $(1)/usr/bin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
