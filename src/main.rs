use hidapi::HidApi;

fn main() {
    let num_tries = 100;

    for i in 0..num_tries {
        println!("Try {}", i);

        let handle: std::thread::JoinHandle<()> = std::thread::Builder::new().name(format!("try {i}")).spawn(enumerate).unwrap();

        handle.join().unwrap();
    }
}

fn enumerate() {
    let api: HidApi = HidApi::new().unwrap();

    for device in api.device_list() {
        println!("{:04x}:{:04x}", device.vendor_id(), device.product_id());
    }
}