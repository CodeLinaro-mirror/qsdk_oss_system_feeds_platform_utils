include $(TOPDIR)/rules.mk

PKG_DISTNAME:=sysupgrade-helper
PKG_NAME:=u-boot
PKG_SOURCE_PROTO:=git
PKG_BRANCH:=master
PKG_RELEASE:=1

include $(INCLUDE_DIR)/local-development.mk
ifeq ($(DUMP)$(PKG_VERSION),)
  PKG_REV:=$(shell git ls-remote $(PKG_SOURCE_URL) $(PKG_BRANCH) | cut -b -7)
  PKG_VERSION:=g$(PKG_REV)
endif

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_DISTNAME)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/sysupgrade-helper
  SECTION:=boot
  CATEGORY:=Boot Loaders
  DEPENDS:=@TARGET_ipq806x||TARGET_ipq_ipq807x_64||TARGET_ipq807x_generic||TARGET_ipq_ipq60xx_64||TARGET_ipq60xx_generic||TARGET_ipq_ipq50xx_64||TARGET_ipq50xx_generic||TARGET_ipq95xx_generic||TARGET_ipq53xx_generic +losetup +libopenssl
  TITLE:=U-boot images tools (dumpimage, mkimage)
endef

HOSTLDFLAGS = \
	      -L$(STAGING_DIR)/usr/lib \
	      -znow -zrelro -pie

SHA_FLAG = "-DUSE_SHA256"

ifneq ($(CONFIG_TARGET_ipq95xx)$(CONFIG_TARGET_ipq807x)$(CONFIG_TARGET_ipq50xx),)
  SHA_FLAG = "-DUSE_SHA384"
endif

define Build/Configure
	mkdir -p $(PKG_BUILD_DIR)/include/config
	echo "CONFIG_FIT=y" >> $(PKG_BUILD_DIR)/include/config/auto.conf
	echo "CONFIG_FIT_PRINT=y" >> $(PKG_BUILD_DIR)/include/config/auto.conf
	echo "CONFIG_TOOLS_FIT=y" >> $(PKG_BUILD_DIR)/include/config/auto.conf
	echo "CONFIG_TOOLS_FIT_PRINT=y" >> $(PKG_BUILD_DIR)/include/config/auto.conf
	touch $(PKG_BUILD_DIR)/include/config/auto.conf
	mkdir -p $(PKG_BUILD_DIR)/include/generated
	echo "#define CONFIG_FIT_PRINT 1" >> $(PKG_BUILD_DIR)/include/generated/autoconf.h
	echo "#define CONFIG_FIT 1" >> $(PKG_BUILD_DIR)/include/generated/autoconf.h
	echo "#define CONFIG_TOOLS_FIT 1" >> $(PKG_BUILD_DIR)/include/generated/autoconf.h
	echo "#define CONFIG_TOOLS_FIT_PRINT 1" >> $(PKG_BUILD_DIR)/include/generated/autoconf.h
	touch $(PKG_BUILD_DIR)/include/generated/autoconf.h
endef

MAKE_FLAGS += \
	CROSS_BUILD_TOOLS=y \
	HOSTCFLAGS="$(SHA_FLAG) -fPIC" \
	HOSTLDFLAGS="$(HOSTLDFLAGS) -lpthread -lcrypto -lssl" \
	HOSTEXTRACFLAGS="$(HOST_EXTRACFLAGS)" \
	no-dot-config-targets=tools-only \
	tools-only

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(MAKE_FLAGS)
endef

define Package/sysupgrade-helper/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/mkimage $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tools/dumpimage $(1)/usr/bin
endef

$(eval $(call BuildPackage,sysupgrade-helper))
