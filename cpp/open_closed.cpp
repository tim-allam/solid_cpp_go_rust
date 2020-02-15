#include <iostream>
#include <vector>

enum class device_colour { black, blue, silver  };
enum class device_weight { light, medium, heavy };

class device_description
{
public:
    explicit device_description(std::string device_name,
                                device_colour d_colour, 
                                device_weight d_weight)
        : device_name_(std::move(device_name)),
          device_colour_(d_colour),
          device_weight_(d_weight) {}

    std::string get_device_name() const 
    {
        return device_name_;
    }

    device_colour get_device_colour() const
    {
        return device_colour_;
    }

    device_weight get_device_weight() const
    {
        return device_weight_;
    }

private:  
    const std::string   device_name_;
    const device_colour device_colour_;
    const device_weight device_weight_;
};

int main()
{
    device_description  headphones {"Sennheiser", device_colour::black, device_weight::light};
    device_description  laptop {"Lenovo T500", device_colour::black, device_weight::medium};
    device_description  printer {"HP G4", device_colour::silver, device_weight::heavy};

    return 0;
}