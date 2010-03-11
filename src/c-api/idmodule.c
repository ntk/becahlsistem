/*-
 * Public platform independent Near Field Communication (NFC) library
 * 
 * Copyright (C) 2009, Roel Verdult
 * Copyright (C) 2010, Leo Hnatek
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

/**
 * @file idmodule.c
 * @brief
 */

#include <python2.6/Python.h>
#include <nfc/nfc.h>

/**
 * This is an implementation for ISO14443A type cards.
 * Basically this functions just returns an identical number.
 */
static PyObject *id_getID (PyObject *self, PyObject *args) 
{ 
  static nfc_device_t *pnd;
  static nfc_target_info_t nti;
  static int uid;

  // Try to open the NFC reader
  pnd = nfc_connect(NULL);

  if (pnd == NULL)
    return PyExc_IOError;
  
  nfc_initiator_init(pnd);

  // Drop the field for a while
  nfc_configure(pnd,NDO_ACTIVATE_FIELD,false);

  // Let the reader only try once to find a tag
  nfc_configure(pnd,NDO_INFINITE_SELECT,false);

  // Configure the CRC and Parity settings
  nfc_configure(pnd,NDO_HANDLE_CRC,true);
  nfc_configure(pnd,NDO_HANDLE_PARITY,true);

  // Enable field so more power consuming cards can power themselves up
  nfc_configure(pnd,NDO_ACTIVATE_FIELD,true);

  //printf("\nConnected to NFC reader: %s\n\n",pnd->acName);

  // Poll for a ISO14443A (MIFARE) tag
  if (nfc_initiator_select_tag(pnd,NM_ISO14443A_106,NULL,0,&nti))
    uid = swap_endian32(nti.nai.abtUid);
  else {
    nfc_disconnect(pnd);
    return PyExc_ValueError;
  }
  
  //printf("%x %d\n", uid, uid);

  nfc_disconnect(pnd);

  //return 0;
  return Py_BuildValue("i", uid);
}

// Method definition - will be inserted into the module 'id' (see below)
static PyMethodDef IdMethods[] = {
    {"getID",  id_getID, METH_VARARGS,
     "Returns an identical number."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

// Py_InitModule() will insert the created module object in the dictionary sys.modules under the key 'id'
PyMODINIT_FUNC initid(void)
{
    (void) Py_InitModule("id", IdMethods);
}

int main(int argc, char *argv[]) {
    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(argv[0]);

    /* Initialize the Python interpreter.  Required. */
    Py_Initialize();

    /* Add a static module */
    initid();
    
    return 0;
}
