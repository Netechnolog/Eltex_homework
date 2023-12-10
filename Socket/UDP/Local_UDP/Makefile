PREFER_SRC_SERV =./Server/
PREFER_SRC_CLIENT =./Client/

TAERGET : client server

client : $(PREFER_SRC_CLIENT)UDP_local_client.c
	gcc $(PREFER_SRC_CLIENT)UDP_local_client.c -o client

server : $(PREFER_SRC_SERV)UDP_local_server.c
	gcc $(PREFER_SRC_SERV)UDP_local_server.c -o server

clean:
	rm server client