/*!
 *  @file SCPI_RP.cpp
 *
 *  This is a library for interacting with Red Pitaya boards via SCPI server
 *
 *
 *  Written by Red Pitaya Industries.
 *
 *  MIT license, all text above must be included in any redistribution
 */

#include "SCPI_RP.h"

#include "common/base_io.h"
#include "network/tcp_scpi.h"
#include "uart/uart_scpi.h"

using namespace scpi_rp;

BaseIO *g_base_io = nullptr;

SCPIRedPitaya::SCPIRedPitaya() {}

SCPIRedPitaya::~SCPIRedPitaya() { delete g_base_io; }

void SCPIRedPitaya::initStream(Stream *serial) {
  UARTInterface *u = new UARTInterface();
  u->init(serial);
  g_base_io = u;
  system.setInterface(u);
  dio.setInterface(u);
  aio.setInterface(u);
  daisy.setInterface(u);
  pll.setInterface(u);
  system_led.setInterface(u);
  gen.setInterface(u);
  acq.control.setInterface(u);
  acq.settings.setInterface(u);
  acq.data.setInterface(u);
  acq.trigger.setInterface(u);
  acq.dma.settings.setInterface(u);
  acq.dma.data.setInterface(u);
}

void SCPIRedPitaya::initClient(Client *client) {
  TCPInterface *c = new TCPInterface();
  c->init(client);
  g_base_io = c;
  system.setInterface(c);
  dio.setInterface(c);
  aio.setInterface(c);
  daisy.setInterface(c);
  pll.setInterface(c);
  system_led.setInterface(c);
  gen.setInterface(c);
  acq.control.setInterface(c);
  acq.settings.setInterface(c);
  acq.data.setInterface(c);
  acq.trigger.setInterface(c);
  acq.dma.settings.setInterface(c);
  acq.dma.data.setInterface(c);
}