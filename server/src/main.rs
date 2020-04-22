#[allow(dead_code)]
use std::net::UdpSocket;
use std::process::Command;
use std::str;
use std::io::{self, Read};
use std::path::{Path,PathBuf};
use std::fs::{
    OpenOptions,
    File,
    read_dir,
    ReadDir,
    DirEntry};
use std::io::Write;
#[allow(unused_imports)]
#[allow(dead_code)]
fn main() {
    
//     * This code block gets the local ip automatically
    //Windows specific obvipo
    let ipcommand = Command::new("powershell")
        .args(&["/C","Get-WmiObject -Class Win32_NetworkAdapterConfiguration -Filter IPENABLED=TRUE | Select IPAddress"])
        .output()
        .expect("Could not get ip");

    let ipraw = str::from_utf8(&ipcommand.stdout).unwrap() as &str;
    let mut ip = String::new();
    for i in (ipraw.find("{").unwrap().. ipraw.find(",").unwrap()) {
        ip.push(ipcommand.stdout[i] as char);
    }
    ip.remove(0); // pops the "{"
    let mut socket = UdpSocket::bind(ip.clone()+":8080");

    if socket.is_ok() {
        println!("Port bind successful");
        println!("UDP socket running \n Local IP: {}:8080",ip);
    } else {
        println!("Port could not be binded");
    }
    //Await M5 connection check-in

    //check_in(&socket.unwrap());

    let deploy_dir = Path::new("Deploy");

     if !deploy_dir.exists() {
        match std::fs::create_dir(deploy_dir) {
                Ok(_) => {println!("Deploy directory has been creted!")},
                Err(e) => {panic!("Error! :{:?}",e)},
            }
     } 
     let mut entries: Vec<String> = deploy_dir.read_dir()
        .unwrap()
        .map(|entry| entry.unwrap().path().into_os_string().into_string().expect("File entry not parsable"))
        .collect();

    let deploy_file = select_file(&deploy_dir);
    println!("Selected file: {}", deploy_file.to_str().unwrap());
}
#[allow(dead_code)]
fn check_in(udp : &UdpSocket) {
    let mut buf:[u8;6] = [0;6];
    
    udp.recv_from(&mut buf).expect("Could not receive UDP data");
    if str::from_utf8(&buf).unwrap() == "start" {
        println!("M5 just checked in!");
    } else {
        println!("Error! Data did not match expected string");
        println!("{:?}", buf);
    }
}

fn select_file(deploy_dir : &Path) -> PathBuf {
    
    let mut option_bullet = 0;
    let mut input = String::new();
    let entries: Vec<DirEntry> = deploy_dir.read_dir().expect("Deploy dir is empty!")
        .map(|entry| entry.expect("Could not get entry!"))
        .collect();
    let mut selected_file = PathBuf::new();
    let mut selection : Result<usize,std::num::ParseIntError>;
    loop {
        println!("Please select a file to deploy: ");
        for (i,x) in entries.iter().enumerate() {
            println!("{}) {}",i+1,x.path().into_os_string().into_string().unwrap().get_mut(deploy_dir.to_str().unwrap().len()+1.. ).unwrap());
        }
        io::stdin().read_line(&mut input).expect("Could not get user input");
        selection = input.parse::<usize>();
        if selection.is_ok() {
            if selection.clone().unwrap()<= entries.len() {
                break;
            } 
        } else {
                println!("Invalid selection. Try again");
            }
    }
    selected_file = entries[selection.unwrap() - 1].path().to_path_buf();
    return selected_file;
}
