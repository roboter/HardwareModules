pin = 2
gpio.mode(pin, gpio.OUTPUT)
gpio.write(pin, gpio.HIGH)
print(gpio.read(pin))