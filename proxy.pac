function FindProxyForURL(url, host)
{
    if (host === "0.0.0.0") {
        return "SOCKS5 127.0.0.1:8888; SOCKS 127.0.0.1:8888"
    }
    return "SYSTEM"
}
