#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QSpinBox>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

    double criticalBandwidth() const { return bandwidth_spin_->value(); }
    double criticalLatency() const { return latency_spin_->value(); }
    double criticalPacketLoss() const { return packet_loss_spin_->value(); }
    int criticalCpuUsage() const { return cpu_spin_->value(); }
    int criticalMemoryUsage() const { return memory_spin_->value(); }

    void setValues(
        double bandwidth, double latency, double packet_loss, int cpu_usage, int memory_usage);

private:
    void setupUi();

    QDoubleSpinBox *bandwidth_spin_ = nullptr;
    QDoubleSpinBox *latency_spin_ = nullptr;
    QDoubleSpinBox *packet_loss_spin_ = nullptr;
    QSpinBox *cpu_spin_ = nullptr;
    QSpinBox *memory_spin_ = nullptr;
    QDialogButtonBox *button_box_ = nullptr;
};

#endif