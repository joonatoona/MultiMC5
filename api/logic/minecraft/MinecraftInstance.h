#pragma once
#include "BaseInstance.h"
#include <java/JavaVersion.h>
#include "minecraft/Mod.h"
#include <QProcess>
#include <QDir>
#include "multimc_logic_export.h"

class ModList;
class WorldList;
class LaunchStep;
class MinecraftProfile;

class MULTIMC_LOGIC_EXPORT MinecraftInstance: public BaseInstance
{
	Q_OBJECT
public:
	MinecraftInstance(SettingsObjectPtr globalSettings, SettingsObjectPtr settings, const QString &rootDir);
	virtual ~MinecraftInstance() {};
	virtual void init() override;


	////// Directories and files //////
	QString jarModsDir() const;
	QString resourcePacksDir() const;
	QString texturePacksDir() const;
	QString loaderModsDir() const;
	QString coreModsDir() const;
	QString libDir() const;
	QString worldDir() const;
	QDir jarmodsPath() const;
	QDir librariesPath() const;
	QDir versionsPath() const;
	QString instanceConfigFolder() const override;
	/// Path to the instance's minecraft directory.
	QString minecraftRoot() const;
	/// Path to the instance's minecraft/bin directory.
	QString binRoot() const;


	//////  Profile management //////
	virtual void createProfile();
	std::shared_ptr<MinecraftProfile> getMinecraftProfile() const;
	void reloadProfile();
	void clearProfile();
	bool reload() override;


	//////  Mod Lists  //////
	std::shared_ptr<ModList> loaderModList() const;
	std::shared_ptr<ModList> coreModList() const;
	std::shared_ptr<ModList> resourcePackList() const;
	std::shared_ptr<ModList> texturePackList() const;
	std::shared_ptr<WorldList> worldList() const;
	virtual QList<Mod> getJarMods() const;


	//////  Mod Lists  //////
	virtual std::shared_ptr<LaunchTask> createLaunchTask(AuthSessionPtr account) override;
	virtual QString createLaunchScript(AuthSessionPtr session) = 0;


	//////  Launch stuff //////
	/// get arguments passed to java
	QStringList javaArguments() const;

	/// get variables for launch command variable substitution/environment
	virtual QMap<QString, QString> getVariables() const override;

	/// create an environment for launching processes
	virtual QProcessEnvironment createEnvironment() override;

	/// guess log level from a line of minecraft log
	virtual MessageLevel::Enum guessLevel(const QString &line, MessageLevel::Enum level) override;

	virtual IPathMatcher::Ptr getLogFileMatcher() override;

	virtual QString getLogFileRoot() override;

	virtual QString getStatusbarDescription() override;

	virtual QStringList getClassPath() const = 0;
	virtual QStringList getNativeJars() const = 0;

	virtual QString getMainClass() const = 0;

	virtual QString getNativePath() const = 0;

	virtual QString getLocalLibraryPath() const = 0;

	virtual QStringList processMinecraftArgs(AuthSessionPtr account) const = 0;

	virtual JavaVersion getJavaVersion() const;

	QString getComponentVersion(const QString &uid) const;
	bool setComponentVersion(const QString &uid, const QString &version);

signals:
	void versionReloaded();

protected:
	QMap<QString, QString> createCensorFilterFromSession(AuthSessionPtr session);
	virtual QStringList validLaunchMethods() = 0;
	virtual QString launchMethod();
	virtual std::shared_ptr<LaunchStep> createMainLaunchStep(LaunchTask *parent, AuthSessionPtr session) = 0;
private:
	QString prettifyTimeDuration(int64_t duration);

protected: // data
	std::shared_ptr<MinecraftProfile> m_profile;
	mutable std::shared_ptr<ModList> m_loader_mod_list;
	mutable std::shared_ptr<ModList> m_core_mod_list;
	mutable std::shared_ptr<ModList> m_resource_pack_list;
	mutable std::shared_ptr<ModList> m_texture_pack_list;
	mutable std::shared_ptr<WorldList> m_world_list;
};

typedef std::shared_ptr<MinecraftInstance> MinecraftInstancePtr;
