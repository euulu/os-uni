const BUF_ADDR: u32 = 0xb8000;
const BUF_HEIGHT: u32 = 25;
const BUF_WIDTH: u32 = 80;

const COLOR_LIGHT_GREEN: u8 = 0xa;
const COLOR_BLACK: u8 = 0x0;

pub const DEFAULT_COLOR: u8 = (COLOR_BLACK << 4) | COLOR_LIGHT_GREEN;

pub struct AsciiChar {
    pub char_byte: u8,
    pub color_byte: u8,
}

pub enum Alignment {
    Left,
    Right,
    Center,
}

pub struct Screen {
    buffer: *mut u8,
    color: u8,
    align: Alignment,
    col_pos: u32,
}

impl core::fmt::Write for Screen {
    fn write_str(&mut self, s: &str) -> core::fmt::Result {
        self.print(s);
        Ok(())
    }
}

impl Screen {
    pub fn new(color: u8, align: Alignment) -> Screen {
        return Screen {
            buffer: BUF_ADDR as *mut u8,
            color,
            align,
            col_pos: 0,
        };
    }

    pub fn print_hello_world(&mut self) {
        let mut i = 0;
        for byte in "Hello world!".bytes() {
            self.write_char(i, AsciiChar { char_byte: byte, color_byte: self.color });
            i += 1;
        }
    }

    pub fn print(&mut self, s: &str) {
        for byte in s.bytes() {
            let byte_offset: u32 = (self.col_pos / BUF_WIDTH + 1) * BUF_WIDTH;

            match byte {
                b'\n' => {
                    while self.col_pos < byte_offset {
                        self.write_char(self.col_pos, AsciiChar { char_byte: b' ', color_byte: self.color });
                        self.col_pos += 1;
                    }
                }
                byte => {
                    self.write_char(self.col_pos, AsciiChar { char_byte: byte, color_byte: self.color });
                    self.col_pos += 1;
                }
            }
        }
    }

    pub fn write_char(&self, offset: u32, char: AsciiChar) {
        unsafe {
            *self.buffer.offset(offset as isize * 2) = char.char_byte;
            *self.buffer.offset(offset as isize * 2 + 1) = char.color_byte;
        }
    }

    pub fn read_char(&self, offset: u32) -> AsciiChar {
        unsafe {
            return AsciiChar {
                char_byte: *self.buffer.offset(offset as isize * 2),
                color_byte: *self.buffer.offset(offset as isize * 2 + 1),
            };
        }
    }
}
