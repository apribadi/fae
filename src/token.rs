pub enum Tag {
    Identifier,
    Eof,
    Error,
}

pub struct Token {
    pub tag: Tag,
    pub start: *const u8,
    pub stop: *const u8,
}
