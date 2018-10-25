/** @file
 *  @brief Battery Service client implementation.
 */

/*
 * Copyright (c) 2018 Nordic Semiconductor
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */
#ifndef __BAS_C_H
#define __BAS_C_H

#include <sys/types.h>
#include <bluetooth/gatt.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>


struct bas_c_evt_handlers;

/**
 * @brief The Battery Service Client instance
 *
 * The instance of the battery service
 */
struct bas_c {
	/** Connection handle */
	struct bt_conn * conn;

	/** Internal values. Use API functions to access this fields. */
	struct {
		/** Current battery value */
		u8_t battery_level;
		/** Handle of CCCD of the Battery Level characteristic */
		u16_t bl_ccd_handle;
		/** Handle of the Battery Level characteristic */
		u16_t bl_handle;
		/** Subscribe parameters */
		bt_gatt_subscribe_params subscribe_params;
		/** Read parameters */
		bt_gatt_read_params read_params;
	} internal;
	/** Callback functions */
	struct const bas_c_evt_handlers * handlers;
};

/**
 * @brief Discovery complete callback
 */
typedef void (*bas_c_dc_func_t)(struct bas_c * bas_c_obj, bool found);

/**
 * @brief Value notify
 */
typedef void (*bas_c_notify_func_t)(struct bas_c * bas_c_obj, u8_t battery_level);

/**
 * @brief Read complete
 */
typedef void (*bas_c_read_func_t)(struct bas_c * bas_c_obj, u8_t battery_level, int err);

/**
 * @brief Subscribed
 */
typedef void (*bas_c_subscribed_func_t)(struct bas_c * bas_c_obj);

/**
 * @brief Unsuscribed
 */
typedef void (*bas_c_unsuscribed_func_t)(struct bas_c * bas_c_obj);

/**
 * @brief Callback structure
 *
 * Structure with callback functions
 */
struct bas_c_evt_handlers {
	bas_c_dc_func_t          on_discovery_complete;
	bas_c_notify_func_t      on_notify;
	bas_c_read_func_t        on_read_complete;
	bas_c_subscribed_func_t  on_subscribed;
	bas_c_unsuscribed_func_t on_unsubscribed;
};

/**
 * @brief Initialization structure
 *
 * Structure that contains initialization parameters.
 */
struct bas_c_init {
	/** Pointer to event handlers */
	struct const bas_c_evt_handlers * handlers;
};

/**
 * @brief
 *
 *
 */
int bas_c_init(struct bas_c * bas_c_obj, struct const bas_c_init * bas_c_init_obj);

int bas_c_uninit(struct bas_c * bas_c_obj);

int bas_c_discovery_start(struct bas_c * bas_c_obj, struct bt_conn * conn);

int bas_c_bl_notif_enable(struct bas_c * bas_c_obj);

int bas_c_bl_notif_disable(struct bas_c * bas_c_obj);

int bas_c_bl_read(struct bas_c * bas_c_obj);

int bas_c_value_get(struct bas_c * bas_c_obj, u8_t * val);

bool bas_c_valid_check(struct bas_c * bas_c_obj);


#endif /* __BAS_C_H  */
