use std::vec::Vec;

#[derive(Clone, Copy, PartialEq)]
enum DeviceColour {
    Black,
    Blue,
    Silver,
}

#[derive(Clone, Copy, PartialEq)]
enum DeviceWeight {
    Light,
    Medium,
    Heavy,
}

#[derive(Clone)]
struct DeviceDescription {
    device_name: String,
    device_colour: DeviceColour,
    device_weight: DeviceWeight,
}

impl DeviceDescription {
    fn new(device_name: String, d_colour: DeviceColour, d_weight: DeviceWeight) -> Self {
        DeviceDescription {
            device_name,
            device_colour: d_colour,
            device_weight: d_weight,
        }
    }

    fn get_device_name(&self) -> &str {
        &self.device_name
    }

    fn get_device_colour(&self) -> DeviceColour {
        self.device_colour
    }

    fn get_device_weight(&self) -> DeviceWeight {
        self.device_weight
    }
}

trait Specification<T> {
    fn is_satisfied(&self, item: &T) -> bool;
}

struct ColourSpecification {
    device_colour: DeviceColour,
}

impl Specification<DeviceDescription> for ColourSpecification {
    fn is_satisfied(&self, device: &DeviceDescription) -> bool {
        self.device_colour == device.get_device_colour()
    }
}

struct WeightSpecification {
    device_weight: DeviceWeight,
}

impl Specification<DeviceDescription> for WeightSpecification {
    fn is_satisfied(&self, device: &DeviceDescription) -> bool {
        self.device_weight == device.get_device_weight()
    }
}

type Devices = Vec<DeviceDescription>;

trait Filter<T> {
    fn filter(&self, items: &Devices, spec: &dyn Specification<T>) -> Devices;
}

struct DeviceFilter;

impl Filter<DeviceDescription> for DeviceFilter {
    fn filter(
        &self,
        all_devices: &Devices,
        specification: &dyn Specification<DeviceDescription>,
    ) -> Devices {
        all_devices
            .iter()
            .filter(|device| specification.is_satisfied(device))
            .cloned()
            .collect()
    }
}

fn main() {
    let headphones = DeviceDescription::new(
        String::from("Sennheiser"),
        DeviceColour::Black,
        DeviceWeight::Light,
    );
    let laptop = DeviceDescription::new(
        String::from("Lenovo T500"),
        DeviceColour::Blue,
        DeviceWeight::Medium,
    );
    let printer = DeviceDescription::new(
        String::from("HP G4"),
        DeviceColour::Silver,
        DeviceWeight::Heavy,
    );

    let all_devices = vec![headphones, laptop, printer];

    let fw = DeviceFilter;
    let light_spec = WeightSpecification {
        device_weight: DeviceWeight::Light,
    };
    let filtered_devices_by_weight = fw.filter(&all_devices, &light_spec);

    for device in filtered_devices_by_weight {
        println!("Device name: {}", device.get_device_name());
    }
}

