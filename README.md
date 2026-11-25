- Built an HTTP/1.1 server from scratch over TCP sockets in C++17, implementing robust request parsing (CRLF/LF-tolerant, case-insensitive headers, chunked and Content-Length bodies), path-based routing with path parameters/query strings, and RFC-compliant response handling.
- Designed a fixed-size thread pool with a bounded connection queue and keep-alive support with idle timeouts, enabling efficient concurrent request handling with predictable resource utilization.
- Implemented static file serving with path traversal protection, conditional requests (ETag/Last-Modified → 304), byte-range (206 Partial Content) responses, virtual hosting via the Host header, the RFC 6455 WebSocket upgrade handshake, and Common Log Format access logging.

