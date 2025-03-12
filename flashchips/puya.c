/*
 * This file is part of the flashrom project.
 *
 * Copyright (C) 2000 Silicon Integrated System Corporation
 * Copyright (C) 2004 Tyan Corp
 * Copyright (C) 2005-2008 coresystems GmbH <stepan@openbios.org>
 * Copyright (C) 2006-2009 Carl-Daniel Hailfinger
 * Copyright (C) 2009 Sean Nelson <audiohacked@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

	{
		.vendor		= "PUYA",
		.name		= "P25Q06H",
		.bustype	= BUS_SPI,
		.manufacture_id	= PUYA_ID,
		.model_id	= PUYA_P25Q06H,
		.total_size	= 64,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 3 x 512 bytes */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
		.probe		= PROBE_SPI_RDID,
		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {256, 256} },
				.block_erase = SPI_BLOCK_ERASE_81,
			}, {
				.eraseblocks = { {4 * 1024, 16} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {64 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.printlock	= SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock		= SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write		= SPI_CHIP_WRITE256,
		.read		= SPI_CHIP_READ,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "PUYA",
		.name		= "P25Q11H",
		.bustype	= BUS_SPI,
		.manufacture_id	= PUYA_ID,
		.model_id	= PUYA_P25Q11H,
		.total_size	= 128,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 3 x 512 bytes */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_UNTESTED,
		.probe		= PROBE_SPI_RDID,
		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {256, 512} },
				.block_erase = SPI_BLOCK_ERASE_81,
			}, {
				.eraseblocks = { {4 * 1024, 32} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 2} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {128 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.printlock	= SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock		= SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write		= SPI_CHIP_WRITE256,
		.read		= SPI_CHIP_READ,
		.voltage	= {2300, 3600},
	},

	{
		.vendor		= "PUYA",
		.name		= "P25Q21H",
		.bustype	= BUS_SPI,
		.manufacture_id	= PUYA_ID,
		.model_id	= PUYA_P25Q21H,
		.total_size	= 256,
		.page_size	= 256,
		/* supports SFDP */
		/* OTP: 3 x 512 bytes */
		.feature_bits	= FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested		= TEST_OK_PREW,
		.probe		= PROBE_SPI_RDID,
		.probe_timing	= TIMING_ZERO,
		.block_erasers	=
		{
			{
				.eraseblocks = { {256, 1024} },
				.block_erase = SPI_BLOCK_ERASE_81,
			}, {
				.eraseblocks = { {4 * 1024, 64} },
				.block_erase = SPI_BLOCK_ERASE_20,
			}, {
				.eraseblocks = { {32 * 1024, 8} },
				.block_erase = SPI_BLOCK_ERASE_52,
			}, {
				.eraseblocks = { {64 * 1024, 4} },
				.block_erase = SPI_BLOCK_ERASE_D8,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_60,
			}, {
				.eraseblocks = { {256 * 1024, 1} },
				.block_erase = SPI_BLOCK_ERASE_C7,
			}
		},
		.printlock	= SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock		= SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write		= SPI_CHIP_WRITE256,
		.read		= SPI_CHIP_READ,
		.voltage	= {2300, 3600},
	},
{
		.vendor         = "PUYA",
		.name           = "P25Q40H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q40H,
		.total_size     = 512, // 512 KB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 128} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 16} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 8} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {512 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {512 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q80H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q80H,
		.total_size     = 1024, // 1 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 256} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 32} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 16} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q16H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q16H,
		.total_size     = 2048, // 2 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 512} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 64} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 32} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {2048 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {2048 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q32H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q32H,
		.total_size     = 4096, // 4 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 1024} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 128} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 64} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {4*1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {4*1024* 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q64H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q64H,
		.total_size     = 8192, // 8 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 2048} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 256} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 128} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {8*1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {8*1024* 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q128H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q128H,
		.total_size     = 16384, // 16 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 4096} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 512} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 256} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {16*1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {16*1024* 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},

	{
		.vendor         = "PUYA",
		.name           = "P25Q256H",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,
		.model_id       = PUYA_P25Q256H,
		.total_size     = 32768, // 32 MB
		.page_size      = 256,
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_OTP,
		.tested         = TEST_UNTESTED,
		.probe          = PROBE_SPI_RDID,
		.probe_timing   = TIMING_ZERO,
		.block_erasers  =
		{
			{ .eraseblocks = { {4 * 1024, 8192} }, .block_erase = SPI_BLOCK_ERASE_20 },
			{ .eraseblocks = { {32 * 1024, 1024} }, .block_erase = SPI_BLOCK_ERASE_52 },
			{ .eraseblocks = { {64 * 1024, 512} }, .block_erase = SPI_BLOCK_ERASE_D8 },
			{ .eraseblocks = { {32*1024 * 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_60 },
			{ .eraseblocks = { {32*1024* 1024, 1} }, .block_erase = SPI_BLOCK_ERASE_C7 }
		},
		.printlock      = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD,
		.unlock         = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD,
		.write          = SPI_CHIP_WRITE256,
		.read           = SPI_CHIP_READ,
		.voltage        = {2300, 3600},
	},
