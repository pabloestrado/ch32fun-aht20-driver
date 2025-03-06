# include "ch32fun.h"
# include "aht20.h"


int main() {
    AHT20Data data;

    SystemInit();

    i2c_init();

    while (1)
    {   
        if(AHT20_read(&data) == AHT20_OK) {
            printf("Temperature: %d Humidity: %d\n", (int)data.temperature, (int)data.humidity);
        }
        else {
            printf("Error reading AHT20 sensor\n");
        }
        Delay_Ms(1000);
    }
    
}