all: llarm-versatile.dtb

llarm-versatile.dtb: llarm-versatile.dts
	dtc -I dts -O dtb -o llarm-versatile.dtb llarm-versatile.dts

clean:
	@rm -f llarm-versatile.dtb
