# Documentation

## socklib.h

### **Static Variables**

`static int sl_socket_error`

contains the value of the last `socket()` error (called from socklib.h)

`static int sl_bind_error`

contains the value of the last `bind()` error (called from socklib.h)

`static int sl_listen_error`

contains the value of the last `listen()` error (called from socklib.h)

### **Functions**


### `char *sl_read(int sock, unsigned int bsize)`

**parameters:** `int sock` socket file descripter.

**returns:** `* char` a pointer to a buffer of `bsize` bytes

**description:** wraps `read()`, reads `bsize` bytes to a (zero'd) buffer and returns a pointer to it. (useful for reading strings)

---

### `int sl_accept(int sock, struct sockaddr *client_address)`

**parameters:** `struct sockaddr *` pointer to a socket address for incoming connection.

**returns:** `int` a socket file descripter.

**description:** accepts a connection from a listener socket 

---

### `int sl_tcp_server(struct sockaddr *serv_addr)`

**parameters:** `struct sockaddr *` pointer to the socket address for the server.

**returns:** `int` a socket file descripter.

**description:** initializes a socket to accept TCP connections. 

---

### PLACEHOLDER (wip)

` sl_udp_server(struct sockaddr *serv_addr)`

**parameters:** `struct sockaddr *` pointer to the socket address for the server.

**returns:** `int` a socket file descripter.

**description:** initializes a socket to accept UDP packets. 

---

### `struct sockaddr *sl_sockaddr()`

**returns:** `struct sockaddr *` A pointer to a new (zero'd) socket address.

**description:** Allocates a new `struct sockaddr` on the heap, returns pointer. 

---


### `int sl_udp()`

**returns:** `int` socket file descripter (or respective error code)

**description:** wraps `socket()`; returns a file descripter for a new udp socket. 

---

### `int sl_tcp()`

**returns:** `int` socket file descripter (or respective error code)

**description:** wraps `socket()`; returns a file descripter for a new tcp socket. 

---

**(setsockopt wrappers)**

---

### `int sl_set_reuseaddr(int sock, int v)`

**returns:** `int`

* `0` on success
* `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_REUSEADDR` to `v` 

---

### `int sl_set_broadcast(int sock, int v)`

**returns:** `int`, `0` on success, `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_BROADCAST` to `v` 

---

### `int sl_set_debug(int sock, int v)`

**returns:** `int`, `0` on success, `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_DEBUG` to `v` 

---

### `int sl_set_keepalive(int sock, int v)`

**returns:** `int`, `0` on success, `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_KEEPALIVE` to `v` 

---

### `int sl_set_debug(int sock, int v)`

**returns:** `int`, `0` on success, `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_DEBUG` to `v` 

---

### `int sl_set_oobinline(int sock, int v)`

**returns:** `int`, `0` on success, `-1` on error

**description:** wraps setsockopt; sets the flag of `SO_DEBUG` to `v` 

