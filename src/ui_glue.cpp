// SPDX-FileCopyrightText: 2023 Jan Nieuwstad <jan.sources@nieuwstad.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <lvgl.h>
#include "state.h"
#include "main.h"
#include "ui/vars.h"
#include "ui/structs.h"


extern "C" {

dcl::measuredStateStruct localstatecopy;
dcl::setStateStruct localsetcopy;

} // extern "C"
