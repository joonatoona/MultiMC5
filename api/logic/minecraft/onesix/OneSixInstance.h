/* Copyright 2013-2017 MultiMC Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "minecraft/MinecraftInstance.h"

#include "minecraft/MinecraftProfile.h"
#include "minecraft/ModList.h"

#include "multimc_logic_export.h"

class MULTIMC_LOGIC_EXPORT OneSixInstance : public MinecraftInstance
{
	Q_OBJECT
public:
	explicit OneSixInstance(SettingsObjectPtr globalSettings, SettingsObjectPtr settings, const QString &rootDir);
	virtual ~OneSixInstance(){};

	virtual QSet<QString> traits() override;

	virtual shared_qobject_ptr<Task> createUpdateTask() override;
	virtual std::shared_ptr<Task> createJarModdingTask() override;
	virtual QString createLaunchScript(AuthSessionPtr session) override;
	QStringList verboseDescription(AuthSessionPtr session) override;

	virtual QStringList extraArguments() const override;

	std::shared_ptr<OneSixInstance> getSharedPtr();

	virtual QString typeName() const override;

	bool canExport() const override
	{
		return true;
	}

	QStringList getClassPath() const override;
	QString getMainClass() const override;

	QStringList getNativeJars() const override;
	QString getNativePath() const override;

	QString getLocalLibraryPath() const override;

	QStringList processMinecraftArgs(AuthSessionPtr account) const override;

protected:
	std::shared_ptr<LaunchStep> createMainLaunchStep(LaunchTask *parent, AuthSessionPtr session) override;
	QStringList validLaunchMethods() override;


};

Q_DECLARE_METATYPE(std::shared_ptr<OneSixInstance>)
