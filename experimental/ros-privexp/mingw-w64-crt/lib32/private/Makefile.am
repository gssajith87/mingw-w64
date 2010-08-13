private_override = \
  lib32/libadvapi32.a \
  lib32/libgdi32.a    \
  lib32/libkernel32.a \
  lib32/libmsvcrt.a   \
  lib32/libntdll.a    \
  lib32/libuser32.a
$(private_override) : lib32/lib%.a: lib32/private/%.def
	$(DTDEF32) $<

