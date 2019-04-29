/* NetworkSocketAPI Example Program
 * Copyright (c) 2015 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "ESP8266Interface.h"
#include "TCPSocket.h"
#include <string.h>

ESP8266Interface wifi(D8, D2, false);
RawSerial pc(USBTX, USBRX);


int main()
{

    pc.baud(115200);
    pc.printf("ESP8266 connection \r\n");

    int ret = wifi.connect("iPhone", "03110311"); //ESP8266Interface
    const char *ip = wifi.get_ip_address();
    const char *mac = wifi.get_mac_address();
    pc.printf("IP address is: %s\r\n", ip ? ip : "No IP");
    pc.printf("MAC address is: %s\r\n", mac ? mac : "No MAC");

//    void *socket;
//    SocketAddress address(&wifi,"172.20.10.10",21);
//    address.set_ip_address("172.20.10.10");
//    address.set_port(41);

//    pc.printf("socket open : %d\r\n",wifi.socket_open((void **)(&socket),NSAPI_TCP));
    //addr.get_ip_address(), addr.get_port()
//    pc.printf("address : %s\r\n",address.get_ip_address());
//    pc.printf("port : %u\r\n",address.get_port());
//    pc.printf("socket connect : %d\r\n",wifi.socket_connect(socket,address));
//    pc.printf("socket connect end\r\n");

//    char buf[256]={0,};
//    pc.printf("socket send : %d\r\n",wifi.socket_send(socket,msg,sizeof msg));
//    while(1){
//        if(wifi.readable()) {
//            pc.printf("socket recv : %d\r\n",wifi.socket_recv(socket,buf,sizeof msg));
//            pc.printf("%s\r\n",buf);
//            break;
//        }
//    }

    if(!wifi.tcpServerStart(41)) {
        pc.printf("error\n");
        return 0;
    }
    wait(2);

    pc.printf("TCP SERVER ON\n");

    while(1) {
        if( wifi.readable()) {
            int id = 0;
            char buf[256] = {0,};
            int ret = wifi.id_recv(&id, buf, sizeof(buf));

            if( ret >= 0) {
                pc.printf("recv: %s from :%d \n", buf, id);
                char temp[256] = {0,};
                strcpy(temp,"echo from server >");
                strcat(temp,buf);
                strcat(temp,"\r\n\r\n");
                int length = strlen(temp);
                wifi.id_send(id, temp, length);
                wait(0.005);

            }
        }
    }

    pc.printf("Done\r\n");
}
