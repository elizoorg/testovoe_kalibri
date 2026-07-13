#include "settings_dialog.h"

#include <QLabel>
#include <QVBoxLayout>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

void SettingsDialog::setupUi()
{
    setWindowTitle("Настройки пороговых значений");
    setMinimumWidth(420);
    setModal(true);

    auto *main_layout = new QVBoxLayout(this);

    auto *network_group = new QGroupBox("Сетевые метрики (NetworkMetrics)", this);
    auto *network_form = new QFormLayout(network_group);

    bandwidth_spin_ = new QDoubleSpinBox(this);
    bandwidth_spin_->setRange(0.1, 10000.0);
    bandwidth_spin_->setValue(10.0);
    bandwidth_spin_->setSuffix(" Мбит/с");
    bandwidth_spin_->setDecimals(1);
    bandwidth_spin_->setToolTip("Полоса пропускания ниже этого значения — критично");
    network_form->addRow("Мин. полоса пропускания:", bandwidth_spin_);

    latency_spin_ = new QDoubleSpinBox(this);
    latency_spin_->setRange(0.1, 10000.0);
    latency_spin_->setValue(100.0);
    latency_spin_->setSuffix(" мс");
    latency_spin_->setDecimals(1);
    latency_spin_->setToolTip("Задержка выше этого значения — критично");
    network_form->addRow("Макс. задержка:", latency_spin_);

    packet_loss_spin_ = new QDoubleSpinBox(this);
    packet_loss_spin_->setRange(0.0, 100.0);
    packet_loss_spin_->setValue(5.0);
    packet_loss_spin_->setSuffix(" %");
    packet_loss_spin_->setDecimals(2);
    packet_loss_spin_->setToolTip("Потери пакетов выше этого значения — критично");
    network_form->addRow("Макс. потери пакетов:", packet_loss_spin_);

    main_layout->addWidget(network_group);

    auto *device_group = new QGroupBox("Статус устройства (DeviceStatus)", this);
    auto *device_form = new QFormLayout(device_group);

    cpu_spin_ = new QSpinBox(this);
    cpu_spin_->setRange(1, 100);
    cpu_spin_->setValue(90);
    cpu_spin_->setSuffix(" %");
    cpu_spin_->setToolTip("Загрузка CPU выше этого значения — критично");
    device_form->addRow("Макс. загрузка CPU:", cpu_spin_);

    memory_spin_ = new QSpinBox(this);
    memory_spin_->setRange(1, 100);
    memory_spin_->setValue(90);
    memory_spin_->setSuffix(" %");
    memory_spin_->setToolTip("Использование памяти выше этого значения — критично");
    device_form->addRow("Макс. использование памяти:", memory_spin_);

    main_layout->addWidget(device_group);

    auto *hint = new QLabel("При превышении указанных значений сервер будет отправлять "
                            "клиентам Log-пакеты с предупреждениями (severity: WARNING).",
                            this);
    hint->setWordWrap(true);
    hint->setStyleSheet("color: #666666; font-style: italic; padding: 5px;");
    main_layout->addWidget(hint);

    button_box_ = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(button_box_, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(button_box_, &QDialogButtonBox::rejected, this, &QDialog::reject);
    main_layout->addWidget(button_box_);
}

void SettingsDialog::setValues(
    double bandwidth, double latency, double packet_loss, int cpu_usage, int memory_usage)
{
    bandwidth_spin_->setValue(bandwidth);
    latency_spin_->setValue(latency);
    packet_loss_spin_->setValue(packet_loss);
    cpu_spin_->setValue(cpu_usage);
    memory_spin_->setValue(memory_usage);
}