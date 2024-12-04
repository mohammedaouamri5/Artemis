# SET UP 
### 1. Clone:
  clone repo
```zsh
git clone --recursive git@github.com:mohammedaouamri5/Artemis.git
```
### 2. build the build system
   -- NOTE : You may have to `chmod +x` to same file
```zsh
vendor/bin/premake/Linux/premake5 --cc=<compiler> --file=Build-Project.lua <build-system>
```
\
  **compiler**       : `gcc` or `clang` \
  **build-system**   : `gmake2` for linux \
  ex : 
```zsh
vendor/bin/premake/Linux/premake5 --cc=gcc --file=Build-Project.lua gmake2
```
### 3. build : 
```zsh
make
```
  -- NOTE : run `make help`
  -- NOTE : for `nvim` users run `bear -- make` to create the `compile_commands.json`

### 4. run :
   run the file
```zsh
./run.sh
```
   
