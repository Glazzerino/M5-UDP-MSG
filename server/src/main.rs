use std::net::UdpSocket;
use std::thread::sleep;
use std::io::{self, Write};
// use ipconfig::Adapter;
fn main() {
    let ip = "192.168.0.16:8080";
    let socket = UdpSocket::bind(ip).expect("Could not bind!");
    println!("> Server started on ip {}",ip);
    let mut buffer = [0;1];
    
    loop {
        let (amt, src) = socket.recv_from(&mut buffer).unwrap();
        print!("{}", buffer[0] as char);   
        io::stdout().flush();
        // std::thread::sleep_ms(20);
    }
    

}