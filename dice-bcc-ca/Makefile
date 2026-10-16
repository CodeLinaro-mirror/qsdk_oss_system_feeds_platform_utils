#
# Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
# SPDX-License-Identifier: BSD-3-Clause-Clear
#

include $(TOPDIR)/rules.mk

PKG_NAME:=dice-bcc-ca
PKG_VERSION:=1.0
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/dice-bcc-ca
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=DICE BCC Client Application
  DEPENDS:=@TARGET_ipq96xx +optee-client
endef

define Package/dice-bcc-ca/description
  Userspace OP-TEE Client Application for DICE BCC certificate retrieval on IPQ platforms.
  This application provides a userspace interface to retrieve DICE (Device Identifier
  Composition Engine) BCC (Boot Certificate Chain) certificates from TME via the DICE BCC
  PTA running in OP-TEE secure world.
endef

TARGET_CFLAGS += -g3 -O0 -Werror -Wall \
	-I$(STAGING_DIR)/usr/include

TARGET_LDFLAGS += \
	-L$(STAGING_DIR)/usr/lib \
	-lteec -lpthread

define Package/dice-bcc-ca/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dice_bcc_ca $(1)/usr/bin/
	$(TARGET_CROSS)strip $(1)/usr/bin/dice_bcc_ca
endef

$(eval $(call BuildPackage,dice-bcc-ca))
