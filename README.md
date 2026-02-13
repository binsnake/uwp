Implementation of https://github.com/klezVirus/SilentMoonwalk for use in payloads.

This was leaked in some circles for a long time, so it might as well get released.
This dates back to circa 2023, made by @ia32e while we were collaborating on a project.

For games, it's detected on EasyAntiCheat for some time.


There's multiple detection vectors.
For one, it leads to duplicated frames located on the stack (although these will not show up while unwinding).
Windows loader also inserts guard pages around stack bounds, which are another giveaway.
Crafted BaseThreadInitThunk frame is not on the first page of stack either.
