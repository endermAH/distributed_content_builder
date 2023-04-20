import pdfkit
from jinja2 import Environment, FileSystemLoader
import pandas as pd
import matplotlib.pyplot as plt
import os


def plot_build_duration(csv_file, save_to, by):
    # чтение csv файла в dataframe
    df = pd.read_csv(csv_file)

    # отбор строк с Metric=BuildDuration
    df_build_duration = df.loc[df['Metric'] == by]
    grouped = df_build_duration.groupby('Iteration')['Value'].mean()
    print(by)
    print(grouped)
    # построение графика
    x = grouped.index
    y = grouped.values

    plt.clf()
    plt.plot(x, y)
    plt.xticks(list(range(int(min(x)), int(max(x))+1)))
    # plt.yticks(np.arange(min(y), max(y)+1, 0.5))
    plt.xlabel('Iteration')
    plt.ylabel(by)
    plt.title(by + ' vs Iteration')
    plt.savefig(save_to)


def generate_report(data):
    wkhtml_path = pdfkit.configuration(wkhtmltopdf="C:/Program Files/wkhtmltopdf/bin/wkhtmltopdf.exe")

    # загрузка шаблона
    env = Environment(loader=FileSystemLoader(r'C:\Diploma\tools\reports'))
    template = env.get_template(r"report_template.html")

    # рендеринг шаблона с данными
    rendered_template = template.render(data).encode("utf-8")

    # сохранение результата рендеринга в HTML файл
    with open("reports/report.html", "wb") as f:
        f.write(rendered_template)

    # генерация PDF из HTML файла
    pdfkit.from_file("reports/report.html", "reports/report.pdf", configuration=wkhtml_path, options={"enable-local-file-access": ""})


plot_build_duration(r"C:\Diploma\test_directory\iteration_metrics.csv", "reports/bd.png", 'BuildDuration')
plot_build_duration(r"C:\Diploma\test_directory\iteration_metrics.csv", "reports/wc.png", 'WholeCache')
plot_build_duration(r"C:\Diploma\test_directory\iteration_metrics.csv", "reports/ac.png", 'AgentCache')

df = pd.read_csv(r"C:\Diploma\test_directory\iteration_metrics.csv")
df_build_duration = df.loc[df['Metric'] == 'BuildDuration']
mean_build_duration = df_build_duration['Value'].mean()
df_whole_data = df.loc[df['Metric'] == 'WholeCache']
max_cache = df_whole_data['Value'].max()

df = pd.read_csv(r"C:\Diploma\test_directory\single_metrics.csv")
agent_count = int(df.loc[df['Metric'] == 'AgentCount']['Value'].mean())
iterations = int(df.loc[df['Metric'] == 'IterationCount']['Value'].mean())
print(agent_count)
print(iterations)

data = {
    'report_title': 'Отчет об имитации',
    'data_volume': str(max_cache) + ' MБ',
    'storage_method': 'Хранить все',
    'avg_content_build_time': str(mean_build_duration) + ' сек',
    'avg_content_build_wait_time': '0 сек',
    'agent_count': agent_count,
    'iterations': iterations,
    'chart_path': "bd.png",
    'ac_path': "ac.png",
    'wc_path': "wc.png"
}

generate_report(data)

os.remove("reports/bd.png")
os.remove("reports/wc.png")
os.remove("reports/ac.png")
os.remove("reports/report.html")
