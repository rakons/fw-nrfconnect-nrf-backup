#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/bas.c)

target_sources_ifdef(CONFIG_BT_GATT_HIDS app PRIVATE
                     ${CMAKE_CURRENT_SOURCE_DIR}/hids.c)
