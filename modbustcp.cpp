#include "modbustcp.h"
#include "networkprotocol.h"
#include "vars.h"

ModbusTcp::ModbusTcp()
{
}

void ModbusTcp::decode(QByteArray& msg)
{/*
    Var * var;
    //Modbus Tcp Frame Format
    //------------------------------------
    //  Name                  // Length  //  Function
    //-----------------------------------
    // Transaction Identifier // 2 bytes // For synchronization between messages of server & client
    // Protocol Idetifier     // 2 bytes // Zero for MODBUS/TCP
    // Length Field	      // 2 bytes // Number of remaining bytes in this frame
    // Unit Identifier	      // 1 byte	 // Slave Address (255 if not used)
    // Function code	      // 1 byte	 // Function codes as in other variants
    // Data bytes	      // n bytes // Data as response or commands
    if ((msg.length() < 8) && (msg.length() < *((short *)(&msg[4]))  + 6))
    {
        //epic fail!

    }
    else
    {
        //ok
        switch(msg[7])
        {
            case 01: // Read Coil Status
            //Modbus Response Example:
            //byte N // Name // Value
            // 7     // Function Code // 0x01
            // 8     // Byte Count    // 0x01
            // 9     // Data          // 0x0A
            //-------------------------------
            // Bin  // 0 / 0 / 0 / 0 / 1 / 0 / 1 / 0 /
            // Hex  //       0       /       A       /
            // Coil // 7 / 6 / 5 / 4 / 3 / 2 / 1 / 0 /
            for(int i = m_startingAddr; i < m_startingAddr + msg[8]; ++i)
            {
                var = globalVarList()[i];
                if(var)
                {
                    //((VarValue*)(var->pValue))->bool =
                };
            };
            break;
            case 03: //Read Holding Registers
            //Modbus Response Example:
            //byte N // Name // Value
            // 7     // Function Code // 0x03
            // 8     // Byte Count    // 0x06
            // 9     // Data          // 0x3A (reg in startingAddr, data high)
            // 10    // Data          // 0x98 (reg in startingAddr, data low, data = 15000)
            // 11    // Data          // 0x13 (reg in startingAddr + 1, data high)
            // 12    // Data          // 0x88 (reg in startingAddr + 1, data low, data = 5000)
            // 11    // Data          // 0x00 (reg in startingAddr + 2, data high)
            // 12    // Data          // 0xC8 (reg in startingAddr + 2, data low, data = 200)
            for(int i = m_startingAddr; i < m_startingAddr + msg[8]; ++i)
            {
            //    globalVarList()[i].
            };

            break;
            case 04: //Read Input Registers
            break;
            case 05: //Force Single Coil
            break;
            case 06: //Preset Single Register
            break;
            case 15: //Force Multiple Coils
            break;
            case 16: //Preset Multiple Registers
            break;
            case 17: //Report Slave id
            // not implemented;
            break;
        default:
        {
            // error

            // see "Introduction to Modbus TCP/IP" p. 17
        };
        }
    }
   // decodedVar.append(Var( ));
    */
    NetworkProtocol::decode(msg);
}
