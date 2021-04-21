#include <iostream>
#include <string>
#include <vector>

enum class device_colour { black, blue, silver  };
enum class device_weight { light, medium, heavy };

// class to hold the description of the particular device
class device_description
{
public:
    explicit device_description(std::string device_name,
                                device_colour d_colour, 
                                device_weight d_weight)
        : device_name_(std::move(device_name)),
          device_colour_(d_colour),
          device_weight_(d_weight) {}

    std::string get_device_name() const noexcept
    {
        return device_name_;
    }

    device_colour get_device_colour() const noexcept
    {
        return device_colour_;
    }

    device_weight get_device_weight() const noexcept
    {
        return device_weight_;
    }

private:  
    const std::string   device_name_;
    const device_colour device_colour_;
    const device_weight device_weight_;
};

template <typename T>
class ispecification
{
public:
    virtual bool is_satisfied(const T & item) const = 0;
};

class colour_speficification : public ispecification<device_description>
{
public:
    explicit colour_speficification(device_colour d_colour)
    : device_colour_ (d_colour) {}

    bool is_satisfied(const device_description & device) const override
    {
        return (device_colour_ == device.get_device_colour());
    }

private:
    const device_colour device_colour_;
};


// definition of weight specification
class weight_speficification : public ispecification<device_description>
{
public:
    explicit weight_speficification(device_weight d_weight)
    : device_weight_ (d_weight) {}

    bool is_satisfied(const device_description & device) const override
    {
        return (device_weight_ == device.get_device_weight());
    }

private:
    const device_weight device_weight_;
};

using devices = std::vector<device_description>;

template <typename T>
class ifilter
{
public:
    virtual devices filter(const devices &, 
                           const ispecification<device_description> &) = 0;
};

class device_filter : public ifilter<device_description>
{
public:
    devices filter(const devices & all_devices, 
                   const ispecification<device_description> & specificaition)
    {
        devices filtered_devices;

        for (const auto & device : all_devices)
        {
            if (specificaition.is_satisfied(device))
                filtered_devices.push_back(device);
        }

        return filtered_devices;
    }
};

int main()
{
    device_description  headphones {"Sennheiser" ,  device_colour::black ,  device_weight::light };
    device_description  laptop     {"Lenovo T500",  device_colour::blue  ,  device_weight::medium};
    device_description  printer    {"HP G4"      ,  device_colour::silver,  device_weight::heavy };

    devices all_devices {headphones, laptop, printer};

    device_filter fw;
    weight_speficification light_spec(device_weight::light);    
    const auto filtered_devices_by_weight = fw.filter(all_devices, light_spec);

    for (const auto & device : filtered_devices_by_weight)
    {
        std::cout << "Device name: " << device.get_device_name()   << std::endl;       
    }

    return 0;
}
