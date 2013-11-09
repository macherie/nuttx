/****************************************************************************
 * include/nuttx/audio/i2s.h
 *
 *   Copyright(C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_NUTTX_AUDIO_I2S_H
#define __INCLUDE_NUTTX_AUDIO_I2S_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef CONFIG_I2S

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/
/* Access macros ************************************************************/

/****************************************************************************
 * Name: I2S_RXSAMPLERATE
 *
 * Description:
 *   Set the I2S RX sample rate.  NOTE:  This will have no effect if (1) the
 *   driver does not support an I2C receiver or if (2) the sample rate is
 *   driven by the I2C frame clock.  This may also have unexpected side-
 *   effects of the RX sample is coupled with the TX sample rate.
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   rate - The I2S sample rate in samples (not bits) per second
 *
 * Returned Value:
 *   Returns the resulting bitrate
 *
 ****************************************************************************/

#define I2S_RXSAMPLERATE(d,f) ((d)->ops->i2s_rxsamplerate(d,r))

/****************************************************************************
 * Name: I2S_RXDATAWIDTH
 *
 * Description:
 *   Set the I2S RX data width.  The RX bitrate is determined by
 *   sample_rate * data_width.
 *
 * Input Parameters:
 *   dev   - Device-specific state data
 *   width - The I2S data with in bits.
 *
 * Returned Value:
 *   Returns the resulting bitrate
 *
 ****************************************************************************/

#define I2S_RXDATAWIDTH(d,b) ((d)->ops->i2s_rxdatawidth(d,b))

/****************************************************************************
 * Name: I2S_RECEIVE
 *
 * Description:
 *   Receive a block of data from I2S.
 *
 * Input Parameters:
 *   dev      - Device-specific state data
 *   buffer   - A pointer to the buffer in which to recieve data
 *   nbytes   - The length of data that can be received in the buffer in number
 *              of bytes.
 *   callback - A user provided callback function that will be called at
 *              the completion of the transfer.  The callback will be
 *              performed in the context of the worker thread.
 *   arg      - An opaque argument that will be provided to the callback
 *              when the transfer complete.
 *   timeout  - The timeout value to use.  The transfer will be canceled
 *              and an ETIMEDOUT error will be reported if this timeout
 *              elapsed without completion of the DMA transfer.  Units
 *              are system clock ticks.  Zero means no timeout.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.  NOTE:  This function
 *   only enqueues the transfer and returns immediately.  Success here only
 *   means that the transfer was enqueued correctly.
 *
 *   When the transfer is complete, a 'result' value will be provided as
 *   an argument to the callback function that will indicate if the transfer
 *   failed.
 *
 ****************************************************************************/

#define I2S_RECEIVE(d,b,n,c,a,t) ((d)->ops->i2s_receive(d,b,n,c,a,t))

/****************************************************************************
 * Name: I2S_TXSAMPLERATE
 *
 * Description:
 *   Set the I2S TX sample rate.  NOTE:  This will have no effect if (1) the
 *   driver does not support an I2C transmitter or if (2) the sample rate is
 *   driven by the I2C frame clock.  This may also have unexpected side-
 *   effects of the TX sample is coupled with the RX sample rate.
 *
 * Input Parameters:
 *   dev  - Device-specific state data
 *   rate - The I2S sample rate in samples (not bits) per second
 *
 * Returned Value:
 *   Returns the resulting bitrate
 *
 ****************************************************************************/

#define I2S_TXSAMPLERATE(d,f) ((d)->ops->i2s_txsamplerate(d,r))

/****************************************************************************
 * Name: I2S_TXDATAWIDTH
 *
 * Description:
 *   Set the I2S TX data width.  The TX bitrate is determined by
 *   sample_rate * data_width.
 *
 * Input Parameters:
 *   dev   - Device-specific state data
 *   width - The I2S data with in bits.
 *
 * Returned Value:
 *   Returns the resulting bitrate
 *
 ****************************************************************************/

#define I2S_TXDATAWIDTH(d,b) ((d)->ops->i2s_txdatawidth(d,b))

/****************************************************************************
 * Name: I2S_SEND
 *
 * Description:
 *   Send a block of data on I2S.
 *
 * Input Parameters:
 *   dev    - Device-specific state data
 *   buffer - A pointer to the buffer of data to be sent
 *   nbytes - the length of data to send from the buffer in number of bytes.
 *   callback - A user provided callback function that will be called at
 *              the completion of the transfer.  The callback will be
 *              performed in the context of the worker thread.
 *   arg      - An opaque argument that will be provided to the callback
 *              when the transfer complete.
 *   timeout  - The timeout value to use.  The transfer will be canceled
 *              and an ETIMEDOUT error will be reported if this timeout
 *              elapsed without completion of the DMA transfer.  Units
 *              are system clock ticks.  Zero means no timeout.
 *
 * Returned Value:
 *   OK on success; a negated errno value on failure.  NOTE:  This function
 *   only enqueues the transfer and returns immediately.  Success here only
 *   means that the transfer was enqueued correctly.
 *
 *   When the transfer is complete, a 'result' value will be provided as
 *   an argument to the callback function that will indicate if the transfer
 *   failed.
 *
 ****************************************************************************/

#define I2S_SEND(d,b,n,c,a,t) ((d)->ops->i2s_send(d,b,n,c,a,t))

/****************************************************************************
 * Public Types
 ****************************************************************************/
/* Transfer complete callback */

typedef CODE void (*i2s_callback_t)(FAR struct i2s_dev_s *dev,
                                    FAR const void *buffer, size_t nbytes,
                                    FAR void *arg, int result);
/* The I2S vtable */

struct i2s_dev_s;
struct i2s_ops_s
{
  /* Receiver methods */

  uint32_t (*i2s_rxsamplerate)(FAR struct i2s_dev_s *dev, uint32_t rate);
  uint32_t (*i2s_rxdatawidth)(FAR struct i2s_dev_s *dev, int bits);
  int      (*i2s_receive)(FAR struct i2s_dev_s *dev, FAR void *buffer,
             size_t nbytes, i2s_callback_t callback, FAR void *arg,
             uint32_t timeout);

  /* Transmitter methods */

  uint32_t (*i2s_txsamplerate)(FAR struct i2s_dev_s *dev, uint32_t rate);
  uint32_t (*i2s_txdatawidth)(FAR struct i2s_dev_s *dev, int bits);
  int      (*i2s_send)(FAR struct i2s_dev_s *dev, FAR const void *buffer,
             size_t nbytes, i2s_callback_t callback, FAR void *arg,
             uint32_t timeout);
};

/* I2S private data.  This structure only defines the initial fields of the
 * structure visible to the I2S client.  The specific implementation may 
 * add additional, device specific fields
 */

struct i2s_dev_s
{
  FAR const struct i2s_ops_s *ops;
};

/****************************************************************************
 * Public Data
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* CONFIG_I2S */
#endif /* __INCLUDE_NUTTX_AUDIO_I2S_H */