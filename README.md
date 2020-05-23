# Привет
Про ArchLinux я постоянно слышу, что "Это что-то сложное" или "Кто установил arch, тот сразу считает элитой в мире GNU/Linux". Этим репозиторием я хочу показать то, насколько изи можно установить (не настроить полностью с xorg).

## Примечание
Этот гайд подойдет тем, у кого есть поддержка UEFI c GPT.

## [Установка Arch Linux](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))

### Скачать и установить на флешку.
[Ссылка](https://www.archlinux.org/download/) на [Arch](https://www.archlinux.org/) для записи образа на флешку.
```
# Находим USB
sudo fdisk -l

# Устанавливаем образ на USB. 
# Путь /dev/sdX должен быть без цифры в конце
sudo dd bs=4M if=/path/to/antergos-x86_64.iso of=/dev/sdX status=progress && sync
```
Загружаем LiveUSB и приступаем к установке ArchLinux.

### [Соединение с Интернетом](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)#%D0%A1%D0%BE%D0%B5%D0%B4%D0%B8%D0%BD%D0%B5%D0%BD%D0%B8%D0%B5_%D1%81_%D0%98%D0%BD%D1%82%D0%B5%D1%80%D0%BD%D0%B5%D1%82%D0%BE%D0%BC)
Проверяем соединение
```
ping -c2 8.8.8.8
```
Если нет соединения (пишет ошибку)
```
# Для прямого подключения по проводу ethernet
dhcpcd

# Для Wi-Fi
wifi-menu
```

### [Разметка дисков](https://wiki.archlinux.org/index.php/Installation_guide_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)#%D0%A0%D0%B0%D0%B7%D0%BC%D0%B5%D1%82%D0%BA%D0%B0_%D0%B4%D0%B8%D1%81%D0%BA%D0%BE%D0%B2)
Разметку делать через `cfdisk`. Так же стоит понимать, что ниже разметка может подойти для тех носителей, у которых соединение происходит по SATA. Может быть такое, что не обязательно `sdX`, но и `nvme0n1`.       
|Раздел|Тип|Размер|
|:-:|:-:|:-:|
|/dev/sda1|EFI|512 МБ|
|/dev/sda2|Linux x86-64 root (/)|Остаток|

### [Форматирование разделов](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Форматирование_разделов)
После создания, форматируем разделы.
```
mkfs.fat -F32 /dev/sda1 && mkfs.ext4 /dev/sda2
```

### [Монтирование раздела](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Монтирование_разделов)
```
mount /dev/sdX1 /mnt
```

### [Установка основных пакетов](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Установка_основных_пакетов)
Можно [выбрать зеркало](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Выбор_зеркал) для более высокой скорости скачивания пакетов (но можно и не ставить).
```
pacstrap /mnt base linux linux-firmware
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
Локализация системы </br>
В файле `/etc/locale.gen` нужно раскомментить `en_US.UTF-8 UTF-8` и `ru_RU.UTF-8 UTF-8`. Потом выполняем команды:
```
locale-gen
echo LANG=en_US.UTF-8 > /etc/locale.conf
echo KEYMAP=ru > /etc/vconsole.conf
```

### [Настройка сети](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Настройка_сети)
Добавьте hostname `echo fromsi-pc > /etc/hostname`. В файле `/etc/hosts` добавьте следующее:
```
127.0.0.1	 localhost
::1		 localhost
127.0.1.1	 fromsi-pc.localdomain	fromsi-pc
```

### [Пароль суперпользователя](https://wiki.archlinux.org/index.php/Installation_guide_(Русский)#Пароль_суперпользователя)
```
passwd
```
### [Установка NetworkManager](https://wiki.archlinux.org/index.php/NetworkManager_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9))
NetworkManager нужен для сети, вот установка
```
pacman -S networkmanager && systemctl enable NetworkManager
```
Так же можно установить `netctl` (я его ставил для ноута с использованием wifi-menu)
```
pacman -S wireless_tools wpa_supplicant dialog
```

### [Загрузчик](https://wiki.archlinux.org/index.php/Arch_boot_process#Boot_loader)
```
1) pacman -S grub efibootmgr dosfstools openssh os-prober mtools linux-headers linux-lts linux-lts-headers
2) mkdir /boot/efi
3) mount /dev/sda1 /boot/efi
4) grub-install --target=x86_64-efi --efi-directory=/boot/efi --bootloader-id=GRUB --removable
6) grub-mkconfig -o /boot/grub/grub.cfg
7) exit
8) unmount -R /mnt
9) reboot
```

### [Добавляем пользователя](https://wiki.archlinux.org/index.php/Users_and_groups_%28%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9%29)
```
pacman -S sudo vim
EDITOR=vim visudo
```
Раскомментировать `%wheel ALL=(ALL) ALL`.
Далее добавляем пользователя (`fromsi` - название пользователя)
```
useradd -m -g users -G wheel,audio -s /bin/bash fromsi && passwd fromsi
```

### [Установка yay](https://github.com/Jguer/yay#installation)
Yet Another Yogurt - An AUR Helper Written in Go
```
cd /tmp && git clone https://aur.archlinux.org/yay.git && cd yay && makepkg -si
```

### Прочие зависимости
Включим [multilib](https://wiki.archlinux.org/index.php/Multilib_(%D0%A0%D1%83%D1%81%D1%81%D0%BA%D0%B8%D0%B9)).
```
pacman -Syu && pacman -S --needed base-devel wget git yajl python python-pip openssh pulseaudio pulseaudio-alsa bash-completion
yay -S nerd-fonts-complete ttf-font-awesome ttf-roboto-mono ttf-material-design-icons-git
```
