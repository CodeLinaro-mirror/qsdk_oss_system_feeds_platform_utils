include $(TOPDIR)/rules.mk

PKG_NAME:=coremark
PKG_VERSION:=1.01

PKG_SOURCE:=v$(PKG_VERSION).zip
PKG_SOURCE_URL:=https://github.com/eembc/coremark/archive
PKG_MD5SUM:=a87572b06cc99c0fcef3501ec45bd0fd
include $(INCLUDE_DIR)/package.mk

define Package/coremark
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=CoreMark EEMBC Benchmark
  URL:=https://github.com/eembc/coremark
endef

define Package/coremark/description
  CoreMark is a simple, yet sophisticated benchmark that is designed specifically to test the functionality of a processor core.
endef

PORT_DIR:=simple
define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) PORT_DIR=$(PORT_DIR) ITERATIONS=200000 $(MAKE_FLAGS) compile
endef

define Package/coremark/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/coremark.exe $(1)/bin/coremark
endef

$(eval $(call BuildPackage,coremark))
