/*
 *  $Id: errorhandler.h,v 1.3 2003/10/06 09:44:56 ajung Exp $
 *
 * SCTP implementation according to RFC 2960.
 * Copyright (C) 2000 by Siemens AG, Munich, Germany.
 *
 * Realized in co-operation between Siemens AG
 * and University of Essen, Institute of Computer Networking Technology.
 *
 * Acknowledgement
 * This work was partially funded by the Bundesministerium für Bildung und
 * Forschung (BMBF) of the Federal Republic of Germany (Förderkennzeichen 01AK045).
 * The authors alone are responsible for the contents.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * There are two mailinglists available at http://www.sctp.de which should be
 * used for any discussion related to this implementation.
 *
 * Contact: discussion@sctp.de
 *          tuexen@fh-muenster.de
 *          ajung@exp-math.uni-essen.de
 *
 * Purpose: This module decodes error chunks and handles them accordingly.
 *          They are sent to the module that can treat these chunks...
 *          For chunks that are not treated in any way, we log their occurrence
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include "globals.h"            /* for chunk struct definition */

void eh_init_errorhandler(void);

/*
 * eh_new: Create a new instance and returns a pointer to its data.
 */
void *eh_new(void);

/* 
 * eh_delete: Deletes a bundling instance
 * 
 * Params: Pointer/handle which was returned by eh_new()
 */
void eh_delete(void *instancePtr);

/*
 *  eh_recv_chunk gets a pointer to an error chunk and decodes it
 *  accordingly....
 *  @return  error code, 0 for success, less than one for error
 */
int eh_recv_chunk(SCTP_simple_chunk * errchunk);

/**
 * function to trigger sending of error chunk, after receiving an invalid stream id
 * @return error value, 0 on success, -1 on error
 */
int eh_make_invalid_streamid_error(unsigned short streamid);


/**
 * function sends the unknown chunk back
 */
int eh_send_unrecognized_chunktype(unsigned char* faulty_chunk, unsigned short length);

/**
 * function to trigger sending of error chunk, after mandatory parameter(s) was(were) missing
 * @return error value, 0 on success, -1 on error
 */
int eh_make_missing_mandatory_param(unsigned int number, unsigned short *param_types);

/**
 * function to trigger sending of error chunk, after receiving an invalid stream id
 * @param number number of pointers passed as second argument
 * @param addresses pointers (or array of pointers) to unrecognized addresses
 * @return error value, 0 on success, -1 on error
 */
int eh_send_unresolvable_address(unsigned int number, unsigned char *addresses);



/**
 * function to add an error chunk, after empty data chunk was received
 * @return error value, 0 on success, -1 on error
 */
int eh_make_empty_data_chunk_error(unsigned int tsn);



#endif
