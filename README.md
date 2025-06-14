# winboom
💣 Because sometimes, you just need to watch the world BSOD.

<img src=".github/bsod.png" width="400"><br>

> [!WARNING]
> BSODs can cause data loss or some files to corrupt, so save everything just in case.

## About
**winboom** is a minimal program both written in C++ designed to cause a BSOD by raising an exception in ntdll.dll in Windows.

It works in any NT-based system (sorry MS-DOS folks).

## How to use
> [!IMPORTANT]
> Since this is really low level stuff, you need to run this program as administrator in order for it to work!

The easy way to use winboom follows like this:
- Go to the **Releases** of this repo.
- Download the latest **winboom.exe** provided.
- Open the file as administrator.
- Click "Yes" in the winboom box.

Now here comes the hard way, if for some reason you want to rebuild this, you can do it.
```sh
cd path\to\winboom
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
And that's it, you have your fresh built **winboom.exe** 

## FAQ
<details>
<summary>My antivirus flagged this as dangerous, what can I do?</summary>

It's totally normal because antiviruses are designed to avoid these stuff to happen, but you can temporarily disable it if you really want to run winboom.exe.
</details>

<details>
<summary>Is there something for Linux?</summary>

Try running this command: `:(){ :|:& };:`
</details>

<details>
<summary>Why did you make this?</summary>

I was heavily bored at my home and with nothing to do, so I remembered that once, a long time ago, I wrote a russian roulette code in Python to BSOD Windows, so I reused that code and translated it to C++.
</details>

<details>
<summary>Can I prank someone with this?</summary>

Sure, but I'm not responsible for any damage caused to physical devices. Proceed with caution!
</details>


## Credits
Made by [PwLDev](https://github.com/PwLDev).
Licensed under the [MIT LIcense](LICENSE).