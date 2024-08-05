BUILD_DIR = build
TARGET = raytracer
OUTPUT = output
IMAGE_NAME = image.ppm

run: generate visualize

clean:
	@rm -rf build

generate: compile
	@mkdir -p $(OUTPUT)
	@$(BUILD_DIR)/$(TARGET) > $(OUTPUT)/$(IMAGE_NAME)

visualize:
	@feh $(OUTPUT)/$(IMAGE_NAME) 2> /dev/null

compile: build
	@cmake --build build

build:
	@cmake -B build
