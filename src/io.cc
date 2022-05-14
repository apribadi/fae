namespace io {
  span<char> Read(Arena& arena, char const * path) {
    // TODO: don't leak file
    // TODO: fewer C-isms
    FILE * file = fopen(path, "rb");
    if (! file) throw runtime_error("io::read - fopen failed!");
    fseek(file, 0, SEEK_END);
    size_t n = ftell(file);
    rewind(file);
    char * buf = arena.MakeArray<char>(n + 1);
    if (fread(buf, 1, n, file) != n) throw runtime_error("io::read - fread failed!");
    fclose(file);
    buf[n] = '\0';
    return span<char>(buf, n + 1);
  }
}
