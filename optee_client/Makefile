include $(TOPDIR)/rules.mk

PKG_NAME:=optee-client
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OP-TEE/optee_client.git
# tag 4.0.0
PKG_SOURCE_DATE:=2023-09-28
PKG_SOURCE_VERSION:=acb0885c117e73cb6c5c9b1dd9054cb3f93507ee
PKG_MIRROR_HASH:=skip

CMAKE_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/optee-client
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=@TARGET_ipq96xx +libuuid
  TITLE:=Normal World Client side of the TEE
  URL:=$(PKG_SOURCE_URL)
endef

MAKE_FLAGS += EXPORT_DIR=$(STAGING_DIR)

define Package/optee-client/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/out/libteec/libteec.so* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/out/libckteec/libckteec.so* $(1)/usr/lib/
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/out/tee-supplicant/tee-supplicant $(1)/usr/sbin/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/tee-supplicant.init $(1)/etc/init.d/tee-supplicant
endef

$(eval $(call BuildPackage,optee-client))
