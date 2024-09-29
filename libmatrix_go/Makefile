TARGET = main
TARGET_DIR = build

all: build

build: lib_lin_x64 lib_lin_x86 lib_win_x64

lib_lin_x64:
	@mkdir -p $(TARGET_DIR)/lin/x64
	go build -buildmode=c-archive \
		-o $(TARGET_DIR)/lin/x64/libmatrix_go_static.a main.go

lib_lin_x86:
	@mkdir -p $(TARGET_DIR)/lin/x86
	GOARCH=386 && \
	go build -buildmode=c-archive \
		-o $(TARGET_DIR)/lin/x86/libmatrix_go_static.a main.go

lib_win_x64:
	@mkdir -p $(TARGET_DIR)/win/x64
	export GOOS=windows && \
	export GOARCH=amd64 && \
	export CGO_ENABLED=1 && \
	export CXX=x86_64-w64-mingw32-g++-posix && \
	export CC=x86_64-w64-mingw32-gcc-posix && \
	go build -buildmode=c-archive \
		-o $(TARGET_DIR)/win/x64/libmatrix_go_static.a main.go

lib_win_x86:
	@mkdir -p $(TARGET_DIR)/win/x86
	export GOOS=windows && \
	GOARCH=386 && \
	export CGO_ENABLED=1 && \
	export CXX=i686-w64-mingw32-g++-posix && \
	export CC=i686-w64-mingw32-gcc-posix && \
	go build -buildmode=c-archive \
		-o $(TARGET_DIR)/win/x86/libmatrix_go_static.a main.go

run:
	@echo "Running the project..."
	go build -o $(TARGET) main.go
	./$(TARGET)

test:
	go test ./matrix

clean:
	@echo "Cleaning up..."
	rm -f $(TARGET)
	rm -rf $(TARGET_DIR)

.PHONY: all build run test clean
