/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2026 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */
/**
 * @file application_font.hpp
 * @brief application font definition
 */
#ifndef APPLICATION_FONT_HPP
#define APPLICATION_FONT_HPP

#include <libmcu/bitmap/bitmap_view.hpp>
#include <mid/font.hpp>

extern libmcu::bitmap::Const_bitmap bitmap_font;
extern libmcumid::Font application_font;

#endif