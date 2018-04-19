/*
 * Copyright (c) 2018 Yubico AB. All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

/*
 * Perform a factory reset on a given authenticator.
 */

#include <openssl/ec.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "fido.h"
#include "compat.h"

int
main(int argc, char **argv)
{
	fido_dev_t	*dev;
	int		 r;

	if (argc != 2) {
		fprintf(stderr, "usage: reset <device>\n");
		exit(EXIT_FAILURE);
	}

	fido_init();

	if ((dev = fido_dev_new()) == NULL)
		errx(1, "fido_dev_new");

	if ((r = fido_dev_open(dev, argv[1])) != FIDO_OK)
		errx(1, "fido_dev_open: %s (0x%x)", fido_strerr(r), r);

	if ((r = fido_dev_reset(dev)) != FIDO_OK)
		errx(1, "fido_reset: %s (0x%x)", fido_strerr(r), r);

	if ((r = fido_dev_close(dev)) != FIDO_OK)
		errx(1, "fido_dev_close: %s (0x%x)", fido_strerr(r), r);

	fido_dev_free(&dev);

	exit(0);
}
