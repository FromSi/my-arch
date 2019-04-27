# Привет
Это руководство, которое подходит мне и заливаю только для того, чтобы я мог спокойно и не задумываясь для своего железа утсанавливать ARCH LINUX.<br />
Буду устанавливать [linux-lts](https://wiki.archlinux.org/index.php/Kernel_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9) "Линукс ядро"), [xorg](https://wiki.archlinux.org/index.php/Xorg_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9) "X серверв"), [i3](https://wiki.archlinux.org/index.php/i3_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9) "Тайловый оконный менеджер i3"), [nvidia](https://wiki.archlinux.org/index.php/NVIDIA_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9) "Драйвер nvidia") и прочие плюшки. <br />
**Не опирайтесь на мой репозиторий, чтобы установить читсый [ARCH](https://www.archlinux.org/download/ "Arch образ")! Операйтесь на [WIKI](https://wiki.archlinux.org/ "Вики от Arch").**

## Немного про моё железо
Чтобы не было вопросов по типу: "А почему нет SWAP?".
* BIOS имеет поддержку UEFI
* GeForce GTX 650 TI
* ОЗУ 16 GB
* HDD 1 TB

## [Установка Arch Linux](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))
В этом подзаголовке будет информация по установке Arch и только.

### Скачать и установить на флешку.
[Ссылка](https://www.archlinux.org/download/) на [Arch](https://www.archlinux.org/) и [команда](https://antergos.com/wiki/ru/uncategorized/create-a-working-live-usb/) для записи образа на флешку.
```
Найти устройство
sudo fdisk -l

Установить на устройство скачанный образ
sudo dd bs=4M if=/path/to/antergos-x86_64.iso of=/dev/sdX status=progress && sync
```

### [Соединение с Интернетом](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)#%D0%A1%D0%BE%D0%B5%D0%B4%D0%B8%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5_%D1%81_%D0%98%D0%BD%D1%82%D0%B5%D1%80%D0%BD%D0%B5%D1%82%D0%BE%D0%BC)
Проверяем соединение
```
ping -c2 8.8.8.8
```
Если нет соединения (пишет ошибку)
```
Это для провода
dhcpcd

Это для Wi-Fi
wifi-menu
```

### [Разметка дисков](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)#%D0%A0%D0%B0%D0%B7%D0%BC%D0%B5%D1%82%D0%BA%D0%B0_%D0%B4%D0%B8%D1%81%D0%BA%D0%BE%D0%B2)
Разметку делать через `cfdisk`
* /dev/sda1    EFI                      512 МБ
* /dev/sda2    Linux x86-64 root (/)    Остаток

### [Форматирование разделов](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Форматирование_разделов)
После создания, форматируем
```
mkfs.fat -F32 /dev/sda1 && mkfs.ext4 /dev/sda2
```

### [Монтирование раздела](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Монтирование_разделов)
```
mount /dev/sdX1 /mnt
```

### [Выбор зеркал](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Выбор_зеркал)
Поставить конкретный серв в приоритет. Нужно открыть `nano /etc/pacman.d/mirrorlist`. Чтобы вырезать `CTRL + K`, чтобы вставить `CTRL + U`.

### [Установка основных пакетов](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Установка_основных_пакетов)
```
pacstrap /mnt base
```

### [Настройка системы](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Настройка_системы)
Сгенерируем файл fstab
```
genfstab -U /mnt >> /mnt/etc/fstab
```
Перейдём к корневому каталогу новой системы
```
arch-chroot /mnt
```
Сгенерируем часовой пояс
```
ln -sf /usr/share/zoneinfo/Asia/Almaty /etc/localtime && hwclock --systohc
```
Локализация
В файле `/etc/locale.gen` раскомментировать `en_US.UTF-8 UTF-8` и `ru_RU.UTF-8 UTF-8`.
```
locale-gen
```
Добавить в файл `/etc/locale.conf` строку `LANG=en_US.UTF-8` и в файл `/etc/vconsole.conf` стоку `KEYMAP=ru`.

### [Настройка сети](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Настройка_сети)
В файл `/etc/hostname` добавить hostname `fromsi-pc` и в файл `/etc/hosts` строки 
```
127.0.0.1	 localhost
::1		 localhost
127.0.1.1	 fromsi-pc.localdomain	fromsi-pc
```

### [Пароль суперпользователя](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Пароль_суперпользователя)
Устанавливаем пароль для суперпользователя
```
passwd
```

### [Загрузчик](https://wiki.archlinux.org/index.php/Arch_boot_process#Boot_loader)
```
1) pacman -S grub efibootmgr dosfstools openssh os-prober mtools linux-headers linux-lts linux-lts-headers
2) mkdir /boot/EFI
3) mount /dev/sda1 /boot/EFI
4) grub-install --target=x86_64-efi --bootloader-id=grub_uefi --recheck
5) cp /usr/share/locale/en\@quot/LC_MESSAGES/grub.mo /boot/grub/locale/en.mo
6) grub-mkconfig -o /boot/grub/grub.cfg
```

### [Добавляем пользователя](https://wiki.archlinux.org/index.php/Users_and_groups_%28%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9%29)
Скачиваем `sudo`
```
pacman -S sudo
```
В файле `/etc/sudoers` раскомментировать `%wheel ALL=(ALL) ALL`, чтобы пользователи группы `wheel` имели доступ к `sudo`.
Далее добавляем пользователя (`fromsi` - название пользователя)
```
useradd -m -g users -G wheel,audio -s /bin/bash fromsi && passwd fromsi
```

### Прочие зависимости
Включим [multilib](https://wiki.archlinux.org/index.php/Multilib_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)).
```
pacman -Syu && pacman -S --needed base-devel wget git yajl python python-pip openssh vim
```

### [Установка NetworkManager](https://wiki.archlinux.org/index.php/NetworkManager_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))
NetworkManager нужен для сети, вот установка
```
pacman -S networkmanager && systemctl enable NetworkManager
```

### [Установка yaourt](https://neblog.info/ustanovka-yaourt-v-arch-linux)
Yaourt крутая вещь, но ее не желательно использовать
```
cd /tmp
git clone https://aur.archlinux.org/package-query.git
cd package-query
makepkg -si
cd ..
git clone https://aur.archlinux.org/yaourt.git
cd yaourt
makepkg -si
cd ..
sudo rm -dR yaourt package-query
```
или одна строка
```
cd /tmp && git clone https://aur.archlinux.org/package-query.git && cd package-query && makepkg -si && cd .. && git clone https://aur.archlinux.org/yaourt.git && cd yaourt && makepkg -si && cd .. && sudo rm -dR yaourt package-query
```

### [Установить оболочку Zsh по умолчанию](https://wiki.archlinux.org/index.php/Command-line_shell_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)#%D0%92%D1%8B%D0%B1%D0%BE%D1%80_%D0%BE%D0%B1%D0%BE%D0%BB%D0%BE%D1%87%D0%BA%D0%B8_%D0%BF%D0%BE_%D1%83%D0%BC%D0%BE%D0%BB%D1%87%D0%B0%D0%BD%D0%B8%D1%8E)
```
yaourt -S zsh zsh-completions && chsh -s /bin/zsh

sh -c "$(wget https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
```

## Установка [Xorg](https://wiki.archlinux.org/index.php/Xorg_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)) и [i3](https://wiki.archlinux.org/index.php/i3_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))
```
pacman -S xorg-server xorg-drivers xorg-xinit i3-gaps
```

## [Настройка xorg](https://wiki.archlinux.org/index.php/Xorg_(Русский)#Настройка)
Создать файл `/etc/X11/xorg.conf.d/00-keyboard.conf` и записать в него
```
Section "InputClass"
        Identifier "system-keyboard"
        MatchIsKeyboard "on"
        Option "XkbLayout" "us,ru"
        Option "XkbModel" "pc105"
        Option "XkbVariant" "qwerty"
        Option "XkbOptions" "grp:alt_shift_toggle"
EndSection
```

## [Настройка Nvidia](https://wiki.archlinux.org/index.php/NVIDIA_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))
Установить командой 
```
sudo pacman -S nvidia-lts
```
Перезапустить `sudo reboot`. Проверить, что в файле `/etc/mkinitcpio.conf` нет `nouveau`.

### [Xorg настройка драйвера](https://wiki.archlinux.org/index.php/NVIDIA_(Русский)#Минимальная_настройка)
В файле `/etc/X11/xorg.conf.d/20-nvidia.conf` нужно написать
```
Section "Device"
        Identifier "Nvidia Card"
        Driver "nvidia"
        VendorName "NVIDIA Corporation"
        Option "NoLogo" "true"
EndSection
```
Либо автоматически настройка через команду `nvidia-xconfig`.

## [Настройка i3](https://wiki.archlinux.org/index.php/i3#i3status)
Для начала скопируйте [всё содержимое](https://github.com/FromSi/my-arch-i3-nvidia-lts-efi/tree/master/arch-root/home/fromsi) в свою домашнюю директорию пользователя!
```
yaourt -S polybar gnome-screenshot rofi rxvt-unicode-pixbuf firefox nitrogen imagemagick mate-power-manager nerd-fonts-complete ttf-font-awesome ttf-roboto-mono {... пишу}
```

### [Установка pywal](https://github.com/dylanaraps/pywal/wiki/Installation)
```
sudo pip3 install pywal
```
... пишу.
... пишу.
... пишу.

## Screenshot
![img](https://github.com/FromSi/my-arch-i3-nvidia-lts-efi/blob/master/screenshot/screenshot.png)
