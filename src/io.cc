namespace io {
  char * read(char const * path) {
    FILE * file = fopen(path, "rb");
    if (!file) throw runtime_error("io::read: fopen failed!");
    fseek(file, 0, SEEK_END);
    i64 n = ftell(file);
    rewind(file);
    char * buf = static_cast<char *>(malloc(n + 1));
    if (!buf) throw runtime_error("io::read: malloc failed!");
    if ((i64) fread(buf, 1, n, file) != n) throw runtime_error("io::read: fread failed!");
    fclose(file);
    buf[n] = '\0';
    return buf;
  }
}
