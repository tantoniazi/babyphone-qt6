# babyphone — Baby Monitor Application (Qt Pilot)

Este é o piloto de reescrita do app `babyphone` (Baby Monitor) do MeeGo/Harmattan, originalmente escrito em Qt 4 / QtDeclarative + C++ com QAudioInput e D-Bus.

O app monitora o áudio ambiente e, quando o volume excede um limite configurável, inicia uma chamada telefônica para o número dos pais.

## Estrutura

```
babyphone-qt6/
├── CMakeLists.txt          # Build CMake (Qt 5.15)
├── main.cpp                # Entry point
├── babyphonedefines.h      # Constantes e chaves de configuração
├── contact.h/cpp           # Modelo de contato (número de telefone)
├── settings.h/cpp          # Configurações da aplicação (QSettings)
├── audiomonitor.h/cpp      # Captura e análise de áudio (QAudioInput)
├── callmonitor.h/cpp       # Monitor de chamadas via D-Bus
├── usernotifier.h/cpp      # Notificação do usuário (chamada/SMS)
├── profileswitcher.h/cpp   # Troca de perfil do sistema
├── babyphone.h/cpp         # Máquina de estados principal (OFF/WAITING/ON)
├── mainwindow.h/cpp        # Janela principal com QQuickView
├── resources.qrc           # Recursos QML embarcados
├── build.sh                # Script de build
├── README.md               # Este arquivo
└── qml/                    # Interface QML
    ├── main.qml            # Janela principal com ApplicationWindow
    ├── MainPage.qml        # Página principal (monitoramento)
    ├── SettingsPage.qml    # Página de configurações
    └── AboutPage.qml       # Página sobre
```

## Stack alvo

- **Qt 5.15** (QQuickView, QtQuick 2.15, QDBus, QAudioInput)
- C++17
- CMake 3.16+

## Funcionalidades

1. **Monitoramento de áudio**: Captura áudio via microfone e analisa o volume
2. **Detecção de threshold**: Quando o som excede o limite, inicia notificação
3. **Chamada de notificação**: Liga para o número dos pais quando detecta barulho
4. **Atendimento de chamadas**: Pode atender chamadas recebidas do número dos pais
5. **Estados**: OFF (inativo), WAITING (aguardando ativação), ON (monitorando ativo)
6. **Configurações**: Número de contato, volume, duração, delays, comportamento de chamadas

## Build

```bash
# Instalar dependências (Arch/Manjaro):
# sudo pacman -S qt5-base qt5-declarative qt5-multimedia qt5-tools

cd babyphone-qt6
chmod +x build.sh
./build.sh
./babyphone
```

## Dependências de runtime

- Qt 5.15+ (Core, Widgets, Quick, DBus, Multimedia)
- D-Bus do sistema (para monitoramento de chamadas - apenas no N9/N950)
- Dispositivo de áudio de entrada (microfone)

## Licença

GNU General Public License v3.0 (mesma do original).
