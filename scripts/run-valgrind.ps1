$ErrorActionPreference = "Stop"

$ImageName = "logger-valgrind"
$BuildDir = "build-linux"

docker build -f Dockerfile.valgrind -t $ImageName .
if ($LASTEXITCODE -ne 0) {
  throw "docker build failed with exit code $LASTEXITCODE"
}

docker run --rm `
  -v "${PWD}:/work" `
  -w /work `
  $ImageName `
  bash -lc "cmake -S . -B $BuildDir -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build $BuildDir && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$BuildDir/logger"
if ($LASTEXITCODE -ne 0) {
  throw "docker run failed with exit code $LASTEXITCODE"
}
