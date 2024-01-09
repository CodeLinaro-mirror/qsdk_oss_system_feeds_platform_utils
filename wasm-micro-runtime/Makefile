include $(TOPDIR)/rules.mk

PKG_NAME:=libwamr
PKG_VERSION:=1.2.2
PKG_RELEASE:=1
PKG_SOURCE:=WAMR-$(PKG_VERSION).tar.gz

PKG_SOURCE_URL:=https://github.com/bytecodealliance/wasm-micro-runtime/archive/refs/tags
PKG_HASH:=d328fc1e19c54cfdb4248b861de54b62977b9b85c0a40eaaeb9cd9b628c0c788
CMAKE_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/wasm-micro-runtime-WAMR-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/$(PKG_NAME)
  SECTION:=libs
  CATEGORY:= Libraries
  MAINTAINER:=Bytecode Alliance
  TITLE:=Library implementing the WebAssembly Micro Runtime
  LICENSE:=Apache License v2.0 with LLVM Exceptions
  DEPENDS:= +libstdcpp
endef

define Package/$(PKG_NAME)/description
 WebAssembly Micro Runtime (WAMR) is a lightweight standalone WebAssembly (Wasm) runtime with small footprint, high performance and highly configurable features for applications cross from embedded, IoT, edge to Trusted Execution Environment (TEE), smart contract, cloud native and so on.
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/libwamr
	$(INSTALL_DATA) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include/libwamr/
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libiwasm.so $(1)/usr/lib/
endef

define Package/${PKG_NAME}/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/product-mini/platforms/linux/iwasm $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/libiwasm.so $(1)/usr/lib
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
