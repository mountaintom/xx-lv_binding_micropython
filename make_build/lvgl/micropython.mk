
################################################################################
# LVGL build rules

MOD_DIR := $(USERMOD_DIR)


LVGL_BINDING_DIR = $(subst /make_build/lvgl,,$(MOD_DIR))
LVGL_DIR = $(LVGL_BINDING_DIR)/lvgl
LVGL_GENERIC_DRV_DIR = $(LVGL_BINDING_DIR)/driver/generic

CFLAGS_USERMOD += -I$(LVGL_BINDING_DIR)
CFLAGS_USERMOD += -I$(LVGL_BINDING_DIR)/include
CFLAGS_USERMOD += -I$(LVGL_DIR)

ALL_LVGL_SRC = $(shell find $(LVGL_DIR) -type f -name '*.h') $(LVGL_BINDING_DIR)/lv_conf.h

LVGL_MPY = $(BUILD)/lv_mpy.c
LVGL_MPY_METADATA = $(BUILD)/lv_mpy.json

CFLAGS_USERMOD += $(LV_CFLAGS) 

$(LVGL_MPY): $(ALL_LVGL_SRC) $(LVGL_BINDING_DIR)/gen/gen_mpy.py 
	$(ECHO) "LVGL-GEN $@"
	$(Q)mkdir -p $(dir $@)
	$(Q)$(PYTHON) $(LVGL_BINDING_DIR)/gen/gen_mpy.py $(LV_CFLAGS) --board=unix --output=$(LVGL_MPY) --include=$(LVGL_BINDING_DIR) --include=$(LVGL_DIR) --include=$(LVGL_BINDING_DIR)/include --module_name=lvgl --module_prefix=lv --metadata=$(LVGL_MPY_METADATA) $(LVGL_DIR)/lvgl.h

.PHONY: LVGL_MPY
LVGL_MPY: $(LVGL_MPY)

CFLAGS_USERMOD += -Wno-unused-function
SRC_USERMOD_LIB_C += $(shell find $(LVGL_DIR)/src $(LVGL_GENERIC_DRV_DIR) -type f -name "*.c")

SRC_USERMOD_C += $(LVGL_MPY)
LDFLAGS_USERMOD += -lSDL2

