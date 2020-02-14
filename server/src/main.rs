use std::net::UdpSocket;
// use ipconfig::Adapter;
fn main() {
    let ip = "192.168.0.8:8080";
    println!("> Server is starting on ip {}!",ip);
    let socket = UdpSocket::bind(ip).expect("Could not bind!");
    let mut buffer = [0;1024];
    let (amt, src) = socket.recv_from(&mut buffer).unwrap();
}