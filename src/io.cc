namespace io {
  span<char> read(arena::t& arena, char const * path) {
    // TODO: don't leak file
    // TODO: fewer C-isms
    FILE * file = fopen(path, "rb");
    if (! file) throw runtime_error("io::read - fopen failed!");
    fseek(file, 0, SEEK_END);
    size_t n = ftell(file);
    rewind(file);
    char * buf = arena.make_array<char>(n + 8);
    if (fread(buf, 1, n, file) != n) throw runtime_error("io::read - fread failed!");
    fclose(file);
    for (int i = 0; i < 8; ++ i) buf[n + i] = '\0';
    return span<char>(buf, n + 8);
  }
}
