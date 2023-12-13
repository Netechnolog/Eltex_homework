SERVER = RAW_UDP_client.c
CLIENT = UDP_inet_server.c
OBJ_SERV = server
OBJ_CLIENT = client

$(OBJ_SERV) : $(SERVER) $(CLIENT)
	gcc $(SERVER) -o $(OBJ_SERV)
	gcc $(CLIENT) -o $(OBJ_CLIENT)

clean:
	rm $(OBJ_CLIENT) $(OBJ_SERV)
